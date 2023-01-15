#include "filter.hpp"

void filter(std::vector<std::string>& str_list, std::vector<std::string>& str_bak, const std::string& input) {
  std::copy_if(
      str_list.begin(),
      str_list.end(),
      std::back_inserter(str_bak),
      // std::ostream_iterator<std::string>(std::cout, "\n"),
      [ & ](const std::string& s) {
        if (input.empty()) {
          return false;
        } else {
          return std::regex_search(s, std::regex(input)) ;
        }
      });
}
