#ifndef _CONFIG_HPP
#define _CONFIG_HPP
#include <string>
#include <vector>

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


struct startup {
  std::vector<std::string> header, item_show, dotfiles_list, paths_list, keymap_list;
  const char *select_next_key, *select_prev_key;
  int radiobox_selected, history_files_selected, dotfiles_selected, paths_selected;
  std::string editor;
  const char* file_browser_cmd;
  const char* find_file_cmd;
  const char* history_files_cmd;
  const char* url;
};


void GetLuaTable(int& n, lua_State*& L, const char* var_name, std::vector<std::string>& var);

namespace StartUp {
  startup setup();
}

#endif
