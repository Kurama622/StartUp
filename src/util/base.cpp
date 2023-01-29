#include "base.hpp"
#include <sys/stat.h>

namespace StartUp {
  // Filter a list of strings based on regular matching rules
  void filter(std::vector<std::string>& str_list, std::vector<std::string>& str_bak, const std::string& rule) {
    std::copy_if(
      str_list.begin(),
      str_list.end(),
      std::back_inserter(str_bak),

      [ & ](const std::string& s) {
        if (rule.empty()) {
          return false;
        } else {
          return std::regex_search(s, std::regex(rule)) ;
        }
      });
  }

  // Get history file list by running cmd
  std::string GetHistoryFiles(const char* cmd) {
    char buffer[1024];
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
      throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
      result += buffer;
    }
    return result;
  }

  // Parse history files from history file list
  std::vector<std::string> HistoryFiles(const char* cmd) {
    std::string output = GetHistoryFiles(cmd);
    std::vector<std::string> oldfiles_list = {};
    const size_t output_size = output.size();
    size_t pre_pos = 0;
    size_t cur_pos = 0;
    size_t _offset = 0;
    for(; cur_pos + _offset < output_size + 1; ) {
      if (output[cur_pos+_offset] == '[' && output[cur_pos + _offset + 1] == '\'') {
        _offset += 2;
        output[cur_pos] = output[cur_pos+_offset];
      }
      else if (output[cur_pos + _offset] == '\'' && output[cur_pos + _offset + 1] == ',' && \
          output[cur_pos + _offset + 2] == ' ' && output[cur_pos + _offset + 3] == '\'') {
        _offset += 3;
        output[cur_pos] = '\0';
        oldfiles_list.push_back((char*)(&(output[0])+pre_pos));
        pre_pos = cur_pos + 1;

      }
      else if (output[cur_pos+_offset] == '\'' && output[cur_pos + _offset + 1] == ']'){
        output[cur_pos] = '\0';
        oldfiles_list.push_back((char*)(&(output[0]) + pre_pos));
      }
      else {
        output[cur_pos] = output[cur_pos + _offset];
      }
      ++cur_pos;
    }
    return oldfiles_list;
  }

  using namespace ftxui;
  Elements GetPreviewContext(const char* cmd) {
    char buffer[2];
    std::string result = "";
    Elements result_vec;
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
      while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        if (*buffer == '\n' || *buffer == '\0' ) {
          // result_vec.push_back( text(result) | size(WIDTH, EQUAL, 100) | size(HEIGHT, LESS_THAN, 45) );
          result_vec.push_back(text(result) | size(WIDTH, EQUAL, 100));
          result = "";
        }
        else {
          result += buffer;
        }
      }
    } catch (...) {
      pclose(pipe);
      throw;
    }
    pclose(pipe);
    return result_vec;
  }

  Elements PreviewContent (std::vector<std::string>& list_bak, int& selected, const std::string& mode) {
    if (mode == "DOT FILES" | mode == "TAG PATHS") {
      for(auto& file : list_bak) {
        file = std::regex_replace(file, std::regex("(^~)"), std::getenv("HOME"));
      }
    }
    struct stat buffer;
    if (stat (list_bak[selected].c_str(), &buffer) == 0) {
      if (buffer.st_mode & S_IFDIR) {
        if (mode == "TAG PATHS") {
          return GetPreviewContext(("ls -l " + list_bak[selected]).c_str());
        } else {
          return {text("This is a dir!")};
        }
      }
      else if (buffer.st_mode & S_IFREG) {
        return GetPreviewContext(("cat " + list_bak[selected]).c_str());
      }
    }
    else {
      return {text("File not exists!")};
      }
  }

  Component ModalComponent(std::function<void()> do_nothing,
                           std::function<void()> hide_modal,
                           Component dotfiles_box,
                           std::string title, 
                           int percent) {
    auto component = Container::Vertical({
        Renderer(dotfiles_box, [=] {
                  return vbox({
                      text({title}) | center,
                      separator(),
                      color(Color::Cyan, dotfiles_box->Render()),
                               }) | yframe;
                 })
             | size(WIDTH, GREATER_THAN, percent)
             | border
    });
    return component;
  }
}
