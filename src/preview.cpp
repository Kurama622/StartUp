#include "preview.hpp"
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Menu, Horizontal, Renderer
#include <stdexcept>
#include <stdio.h>

#include<string>
#include<sstream>

using namespace ftxui;
Elements exec(const char* cmd) {
    char buffer[2];
    std::string result = "";
    Elements result_vec;
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
          if (*buffer == '\n' || *buffer == '\0' ) {
            // result_vec.push_back( text(result) | size(WIDTH, EQUAL, 100) | size(HEIGHT, LESS_THAN, 45) );
            result_vec.push_back( text(result) | size(WIDTH, EQUAL, 100) );
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
// Elements split(std::string the_text) {
  // Elements output;
  // std::stringstream ss(result);
  // std::string line;
  // while (std::getline(ss, line))
  // //   output.push_back(text(line));
  //   output.push_back(paragraph(line) |  size(HEIGHT, GREATER_THAN, 10));
  // return output;
// }
    return result_vec;
}
