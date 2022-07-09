#ifndef _CONFIG_HPP
#define _CONFIG_HPP
#include <string>
#include<vector>

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

#if (LUA_VERSION_NUM > 501)
  #define LUAL_LEN luaL_len
#else 
  #define LUAL_LEN lua_objlen
#endif

#define MAX_USERID_LENGTH 32

const std::vector<std::string> radiobox_list = {
  "Recently Opened Files         <o>",
  "Find File                     <f>",
  "File Browser                  <b>",
  "Open Dotfiles                 <d>",
  "Tag Paths                     <p>",
  "Exit                        <Esc>"
};


struct startup {
  std::vector<std::string> header, dotfiles_list, paths_list;
  int radiobox_selected, oldfiles_selected, dotfiles_selected, paths_selected;
  std::string editor;
  const char* file_browser_cmd;
  const char* find_file_cmd;
  const char* oldfiles_cmd;
  const char* url;
};


void GetLuaTable(int& n, lua_State*& L, const char* var_name, std::vector<std::string>& var);

namespace StartUp {
  startup setup();
}

#endif
