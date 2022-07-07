#include <fstream>
#include <stdexcept>
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include "oldfiles.hpp"

namespace StartUp {
  std::string Exec(const char* cmd) {
    /* std::array<char, 128> buffer; */
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

  std::vector<std::string> RecentlyOpenFile(const char* cmd) {
    std::string output = Exec(cmd);
    std::vector<std::string> oldfiles_list = {};
    /* std::vector<std::string>* oldfiles_list = new std::vector<std::string>{}; */
    const size_t output_size = output.size();
    size_t pre_pos = 0;
    size_t cur_pos = 0;
    size_t _offset = 0;
    for(; cur_pos+_offset < output_size + 1; ) {
      if (output[cur_pos+_offset]=='[' && output[cur_pos+_offset+1] == '\'') {
        _offset += 2;
        output[cur_pos] = output[cur_pos+_offset];
      }
      else if (output[cur_pos+_offset]=='\'' && output[cur_pos+_offset+1]==',' && \
                  output[cur_pos+_offset+2] == ' ' && output[cur_pos+_offset+3]=='\'') {
        _offset += 3;
        // output[cur_pos] = '\n';
        output[cur_pos] = '\0';
        /* oldfiles_list->push_back((char*)(&(output[0])+pre_pos)); */
        oldfiles_list.push_back((char*)(&(output[0])+pre_pos));
        pre_pos = cur_pos+1;

      }
      else if (output[cur_pos+_offset]=='\'' && output[cur_pos+_offset+1]==']'){
          output[cur_pos] = '\0';
          /* oldfiles_list->push_back((char*)(&(output[0])+pre_pos)); */
        oldfiles_list.push_back((char*)(&(output[0])+pre_pos));
        }
      else {
        output[cur_pos] = output[cur_pos+_offset];
      }
      ++cur_pos;
    }
    return oldfiles_list;
  }
}
