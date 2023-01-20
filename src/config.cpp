#include "config.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>


void GetLuaTable(int& n, lua_State*& L, const char* var_name, std::vector<std::string>& var) {
  lua_getglobal(L, var_name);
  n = LUAL_LEN(L,-1);
  for ( int i = 0; i < n; ++i) {
    lua_pushnumber(L, i+1);
    lua_gettable(L, -2);
    var.push_back(lua_tostring(L,-1));
    lua_pop(L,1);
  }
}

std::string FlexString(const std::string& str) {
  std::stringstream ss;
  ss << std::setw(5) << str;
  return ss.str();
}

namespace StartUp {
  startup setup() {
    const std::vector<const char *> sp_item_key = {
      "history_files_key",
      "find_file_key",
      "file_browser_key",
      "open_dotfiles_key",
      "tag_paths_key",
      "exit_key"
    };

    const std::vector<std::string> sp_item_list = {
      "History Files               ",
      "Find File                   ",
      "File Browser                ",
      "Open Dotfiles               ",
      "Tag Paths                   ",
      "Exit                        "
    };

    std::vector<std::string> header;
    std::vector<std::string> item_show;
    std::vector<std::string> keymap_list;
    std::vector<std::string> dotfiles_list;
    std::vector<std::string> paths_list;

    std::string HOME = std::getenv("HOME");
    lua_State*  L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, (HOME+"/.config/StartUp/config.lua").c_str());
    int n;
    lua_getglobal(L, "style");
    const char* style = lua_tostring(L,-1);
    lua_pop(L,1);

    // lua_getglobal(L, "history_files_key");
    // item_show.push_back(FlexString(lua_tostring(L,-1))) ;
  
    const int N_item = sp_item_list.size();
    for(int i = 0; i < N_item; i++) {
      lua_getglobal(L, sp_item_key[i]);
      const char* keymap = lua_tostring(L,-1);
      keymap_list.push_back(keymap) ;
      item_show.push_back(sp_item_list[i] + FlexString(keymap)) ;
      lua_pop(L,1);
    }

    // lua_pop(L,1);
    //dotfiles_list
    GetLuaTable(n, L, "dotfiles_list", dotfiles_list);

    //paths_list
    GetLuaTable(n, L, "paths_list", paths_list);

    // radiobox_selected
    lua_getglobal(L, "radiobox_selected");
    int radiobox_selected = lua_tonumber(L, -1);

    // oldfiles_selected
    lua_getglobal(L, "oldfiles_selected");
    int oldfiles_selected = lua_tonumber(L, -1);

    // dotfiles_selected
    lua_getglobal(L, "dotfiles_selected");
    int dotfiles_selected = lua_tonumber(L, -1);

    // paths_selected
    lua_getglobal(L, "paths_selected");
    int paths_selected = lua_tonumber(L, -1);

    // editor
    lua_getglobal(L, "editor");
    std::string editor = lua_tostring(L, -1);

    // file_browser_cmd
    lua_getglobal(L, "file_browser_cmd");
    const char* file_browser_cmd = lua_tostring(L, -1);

    // find_file_cmd
    lua_getglobal(L, "find_file_cmd");
    const char* find_file_cmd = lua_tostring(L, -1);

    // oldfiles_cmd
    lua_getglobal(L, "oldfiles_cmd");
    const char* oldfiles_cmd = lua_tostring(L, -1);

    // url
    lua_getglobal(L, "url");
    const char* url = lua_tostring(L, -1);

    // header
    luaL_dofile(L, (HOME+"/.config/StartUp/header/header.lua").c_str());
    lua_getglobal(L, style);
    int ret = lua_pcall(L, 0, 1, -1);
    n = LUAL_LEN(L,-1);
     for (int i = 0; i < n; ++i) {
       lua_pushnumber(L, i+1);
       lua_gettable(L, -2);
       header.push_back(lua_tostring(L,-1));
       lua_pop(L,1);
     }
    return {
      header, item_show, dotfiles_list, paths_list, keymap_list,
      radiobox_selected, oldfiles_selected, dotfiles_selected, paths_selected, 
      editor,
      file_browser_cmd, find_file_cmd, oldfiles_cmd, url
    };
  }
}


