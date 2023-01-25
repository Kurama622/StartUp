#include <regex>
#include <string>      // for string, basic_string, operator+, to_string
#include "ftxui/dom/elements.hpp"

namespace StartUp
{
  void filter(std::vector<std::string>& str_list, std::vector<std::string>& str_bak, const std::string& input);
  std::string GetHistoryFiles(const char* cmd);
  std::vector<std::string> HistoryFiles(const char* cmd);
  ftxui::Elements GetPreviewContext(const char* cmd);
  ftxui::Elements PreviewContent (std::vector<std::string>& oldfiles_list_bak, int& oldfiles_selected);
}
