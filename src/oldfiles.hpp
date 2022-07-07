#ifndef _OLDFILES_HPP
#define _OLDFILES_HPP
#include <vector>
#include <string>

namespace StartUp {
  std::string Exec(const char* cmd);
  std::vector<std::string> RecentlyOpenFile(const char* cmd);
}
#endif
