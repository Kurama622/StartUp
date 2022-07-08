#ifndef _CONFIG_HPP
#define _CONFIG_HPP
#include <string>
#include<vector>

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

#define MAX_USERID_LENGTH 32

// // header: ghost, melting, black_outline, hand_writing
// const std::vector<std::string> header             = {
//   #include "../header/ghost"
// };
// const char * url                       = "https://github.com/StubbornVegeta/StartUp";
// // function
const std::vector<std::string> radiobox_list = {
  "Recently Opened Files         <o>",
  "Find File                     <f>",
  "File Browser                  <b>",
  "Open Dotfiles                 <d>",
  "Tag Paths                     <p>",
  "Exit                        <Esc>"
};


// const std::vector<std::string> dotfiles_list = {
//   "~/.zshrc",
//   "~/.tmux.conf",
//   "~/.config/nvim/init.lua",
//   "~/.config/ranger/rc.conf",
//   "~/.config/zsh/module/aliases.zsh",
//   "~/.config/StartUp/src/config.hpp",
// };
// 
// const std::vector<std::string> paths_list = {
//   "~/.config/StartUp",
//   "~/.config/StartUp/src",
//   "~/.config/StartUp/build",
//   "~/.config",
//   "~/.config/nvim",
//   "~/.config/ranger",
//   "~/.config/zsh/module",
// };
// 
// // default select radiobox number
// int radiobox_selected                 = 0;
// int oldfiles_selected                 = 0;
// int dotfiles_selected                 = 0;
// int paths_selected                    = 0;
// const std::string editor              = "nvim";
// const char* file_browser_cmd          = "ranger";
// const char* find_file_cmd             = "nvim $(fzf)";
// const char* oldfiles_cmd              = "nvim --headless -u NONE -c'echo v:oldfiles | qall!' 2>&1";


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
