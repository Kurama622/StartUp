#ifndef _STARTUP_KEYMAP_H
#define _STARTUP_KEYMAP_H

#include "ftxui/component/event.hpp"               // for Event
#include "ftxui/screen/screen.hpp"
#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include <string>      // for string, basic_string, operator+, to_string
#include "ui.hpp"

namespace StartUp {
  using namespace ftxui;
  Event keymap_transform(const std::string& keymap);
  // const Event KEY_CLOSE = keymap_transform(conf.keymap_list[5]);
  // extern const Event KEY_CLOSE;

  // auto KeyCallback = [&](Event event) {
  //   if (!history_files_shown && !dotfiles_shown && !paths_shown && event == KEY_CLOSE ) {
  //     screen.ExitLoopClosure()();
  //     return true;
  //   }
  //   if (history_files_shown && event == KEY_CLOSE) {
  //     history_files_shown = false;
  //     return true;

  //   }
  //   if (dotfiles_shown && event == KEY_CLOSE ) {
  //     dotfiles_shown = false;
  //     return true;
  //   }
  //   if (paths_shown && event == KEY_CLOSE ) {
  //     paths_shown = false;
  //     return true;
  //   }
  //   if ( !(history_files_shown ^ dotfiles_shown ^ paths_shown) && event == keymap_transform(conf.keymap_list[0])) {
  //     history_files_shown = true;
  //     return true;
  //   }
  //   if ( !(history_files_shown ^ dotfiles_shown ^ paths_shown) && event == keymap_transform(conf.keymap_list[3])) {
  //     dotfiles_shown = true;
  //     return true;
  //   }
  //   if ( !(history_files_shown ^ dotfiles_shown ^ paths_shown) && event == keymap_transform(conf.keymap_list[4])) {
  //     paths_shown = true;
  //     return true;
  //   }
  //   if ( !(history_files_shown ^ dotfiles_shown ^ paths_shown) && event == keymap_transform(conf.keymap_list[1])) {
  //     screen.ExitLoopClosure()();
  //     system(conf.find_file_cmd);
  //     return true;
  //   }
  //   if ( !(history_files_shown ^ dotfiles_shown ^ paths_shown) && event == keymap_transform(conf.keymap_list[2])) {
  //     screen.ExitLoopClosure()();
  //     system(conf.file_browser_cmd);
  //     return true;
  //   }
  //   // <enter> select a item
  //   if (!history_files_shown && !dotfiles_shown && !paths_shown && event == Event::Return) {
  //     ui.options_box->OnEvent(event);
  //     switch(conf.radiobox_selected) {
  //       case 0:
  //         history_files_shown = true;
  //         break;
  //       case 1:
  //         screen.ExitLoopClosure()();
  //         system(conf.find_file_cmd);
  //         break;
  //       case 2:
  //         screen.ExitLoopClosure()();
  //         system(conf.file_browser_cmd);
  //         break;
  //       case 3:
  //         dotfiles_shown = true;
  //         break;
  //       case 4:
  //         paths_shown = true;
  //         break;
  //       case 5:
  //         screen.ExitLoopClosure()();
  //         break;
  //     }
  //     return true;
  //   }
  //   if (history_files_shown && event == Event::Return) {
  //     ui.history_files_box->OnEvent(event);
  //     history_files_shown = false;
  //     screen.ExitLoopClosure()();
  //     system((conf.editor + " " + ui.history_files_list_bak[conf.history_files_selected]).c_str());
  //     return true;
  //   }
  //   if (dotfiles_shown && event == Event::Return) {
  //     ui.dotfiles_box->OnEvent(event);
  //     dotfiles_shown = false;
  //     screen.ExitLoopClosure()();
  //     system((conf.editor + " " + conf.dotfiles_list[conf.dotfiles_selected]).c_str());
  //     return true;
  //   }
  //   if (paths_shown && event == Event::Return) {
  //     ui.paths_box->OnEvent(event);
  //     screen.ExitLoopClosure()();
  //     paths_shown = false;
  //     system((std::string("echo cd ") + conf.paths_list[conf.paths_selected] + "> /tmp/startup_cd.sh").c_str());
  //     return true;
  //   }
  //   return false;
  // };
  bool KeyCallback(ScreenInteractive& screen, UI& ui, Event& event);
  // bool KeyCallback(Screen& screen, Event event);
}
#endif //_KEYMAP_H
