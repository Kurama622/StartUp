#ifndef _STARTUP_BASE
#define _STARTUP_BASE
#include <regex>
#include <string>      // for string, basic_string, operator+, to_string
#include "ftxui/dom/elements.hpp"

#include "ftxui/component/component.hpp"           // for Radiobox
namespace StartUp
{
  void filter(std::vector<std::string>& str_list, std::vector<std::string>& str_bak, const std::string& input);
  std::string GetHistoryFiles(const char* cmd);
  std::vector<std::string> HistoryFiles(const char* cmd);
  ftxui::Elements GetPreviewContext(const char* cmd);
  ftxui::Elements PreviewContent (std::vector<std::string>& list_bak, int& selected, const std::string& mode);
}

#endif //_STARTUP_BASE
