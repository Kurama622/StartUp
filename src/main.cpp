#include <algorithm>
#include <iostream>
#include<vector>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Radiobox
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/component/event.hpp"               // for Event
#include "unistd.h"

#include "oldfiles.hpp"
#include "modal.hpp"
#include "config.hpp"

#include "ftxui/dom/flexbox_config.hpp"
#include "filter.hpp"
#include "preview.hpp"
#include <sys/stat.h>

using namespace ftxui;


startup conf = StartUp::setup();

Component Document(Elements elements, Component radiobox) {
  return Renderer(radiobox, [=] {
    return hbox({
      vbox({
        vbox({
          std::move(elements) | center,
        }),
        text("") | center,
        text("") | center,
        color(Color::Cyan, radiobox->Render()) | center,
        text("") | center,
        text("") | center,
        color(Color::Yellow, text(conf.url)) | center,
      }) | vcenter | flex,
    });
  });}

Component ModalComponent(std::function<void()> do_nothing,
                         std::function<void()> hide_modal,
                         Component dotfiles_box,
                         std::string title, 
                         int percent) {
  auto component = Container::Vertical({
      Renderer(dotfiles_box, [=] {
                return vbox({
                    text({title}) | center,
                    separator(),
                    color(Color::Cyan, dotfiles_box->Render()),
                             }) | yframe;
               })
           | size(WIDTH, GREATER_THAN, percent)
           | border
  });
  // Polish how the two buttons are rendered:
  //
  // component |= Renderer([&](Element inner ) {
  //   return vbox({
  //              inner,
  //          })
  //          | size(WIDTH, GREATER_THAN, 100) 
  //          | border;                        
  // });
  return component;
}

inline bool exists_if (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0); 
}

int main(void) {
  auto screen = ScreenInteractive::Fullscreen();
  Elements elements;
  for (const std::string& it : conf.header) {
    elements.push_back(color(Color::Green, text(it)));
  }
  auto radiobox = Radiobox(&radiobox_list, &conf.radiobox_selected);
  auto main_container = Container::Horizontal({
      Document(elements, radiobox) | flex,
  });

  // State of the application:
  bool oldfiles_shown = false;
  bool dotfiles_shown = false;
  bool paths_shown    = false;

  // oldfiles
  std::vector<std::string> oldfiles_list = StartUp::RecentlyOpenFile(conf.oldfiles_cmd);
  std::vector<std::string> oldfiles_list_bak = oldfiles_list;
  std::string file_name;
  std::string file_name_bak = file_name;
  Component input_box = Input(&file_name, "") | color(Color::White);

  Component oldfiles_box =
      Menu(&oldfiles_list_bak, &conf.oldfiles_selected);

  Component oldfiles_container = Container::Vertical({
      input_box  ,
      oldfiles_box ,
  });


  std::vector<std::string> wraps = {
      "NoWrap",
      "Wrap",
      "WrapInversed",
  };

  // std::vector<std::string> _direction = {"Column", };
  std::vector<std::string> directions = {
      "Row",
      "RowInversed",
      "Column",
      "ColumnInversed",
  };

  auto oldfiles_renderer = Renderer(oldfiles_container, [&] {
    if (file_name != file_name_bak) {
      file_name_bak = file_name;
      oldfiles_list_bak.clear();
      conf.oldfiles_selected = 0;
      // menu_entries_bak = {""};
      filter(oldfiles_list, oldfiles_list_bak, file_name);
      if (file_name.empty() && oldfiles_list_bak.empty()) {
         oldfiles_list_bak = oldfiles_list;
      }
    }
    // FlexboxConfig config;
    Elements con = {};
    if (!oldfiles_list_bak.empty()) {
      if(exists_if(oldfiles_list_bak[conf.oldfiles_selected]))
        con = exec(("cat " + oldfiles_list_bak[conf.oldfiles_selected]).c_str());
      else {
        con = {text("The file is not exist")};
      }
    }

    // auto _wrap = FlexboxConfig().Set(FlexboxConfig::Wrap::Wrap)
    //                             .Set(FlexboxConfig::Direction::Column);
    return vbox( {
                  vbox({
                      window(text("") , hbox( {color(Color::Green, text("-> ")) | blink  , vbox(input_box->Render()) })) | size(HEIGHT, EQUAL, 5 ) ,
                  }),
                  vbox({
                    window(text("HISTORY FILES") | hcenter, vbox(color(Color::Cyan, oldfiles_box->Render())) | yframe) | size(HEIGHT, EQUAL, 45 ) | size(WIDTH, EQUAL, 90 ),
                    window(text("PREVIEW") | hcenter, color(Color::Cyan, vbox(con))) | size(HEIGHT, EQUAL, 45) | size(WIDTH, EQUAL, 90 ),
                   })
                });
  });
  // auto oldfiles_box = Menu(&oldfiles_list, &conf.oldfiles_selected);




  auto dotfiles_box = Menu(&conf.dotfiles_list, &conf.dotfiles_selected);
  auto paths_box = Menu(&conf.paths_list, &conf.paths_selected);
 

  // Some actions modifying the state:
  /* auto show_oldfiles = [&] { oldfiles_shown = true; }; */
  /* auto show_dotfiles = [&] { dotfiles_shown = true; }; */
  auto hide_modal = [&] { oldfiles_shown = false; dotfiles_shown = false; paths_shown = false;};
  auto do_nothing = [&] {};
  // auto oldfiles_component = ModalComponent(do_nothing, hide_modal, oldfiles_box, "Recently Open File", 100);
  auto dotfiles_component = ModalComponent(do_nothing, hide_modal, dotfiles_box, "Open Dotfiles", 70);
  auto paths_component = ModalComponent(do_nothing, hide_modal, paths_box, "Tag Paths", 70);
  main_container |= Modal(oldfiles_renderer, &oldfiles_shown);
  main_container |= Modal(dotfiles_component, &dotfiles_shown);
  main_container |= Modal(paths_component, &paths_shown);

  auto component = CatchEvent(main_container, [&](Event event) {
    if (!oldfiles_shown && !dotfiles_shown && !paths_shown && event == Event::Escape ) {
      screen.ExitLoopClosure()();
      return true;
    }
    if (oldfiles_shown && event == Event::Escape ) {
      oldfiles_shown = false;
      return true;
    }
    if (dotfiles_shown && event == Event::Escape ) {
      dotfiles_shown = false;
      return true;
    }
    if (paths_shown && event == Event::Escape ) {
      paths_shown = false;
      return true;
    }
    if ( !(oldfiles_shown ^ dotfiles_shown ^ paths_shown) && event == Event::Character('o')) {
      oldfiles_shown = true;
      return true;
    }
    if ( !(oldfiles_shown ^ dotfiles_shown ^ paths_shown) && event == Event::Character('d')) {
      dotfiles_shown = true;
      return true;
    }
    if ( !(oldfiles_shown ^ dotfiles_shown ^ paths_shown) && event == Event::Character('p')) {
      paths_shown = true;
      return true;
    }
    if ( !(oldfiles_shown ^ dotfiles_shown ^ paths_shown) && event == Event::Character('f')) {
      screen.ExitLoopClosure()();
      system(conf.find_file_cmd);
      return true;
    }
    if ( !(oldfiles_shown ^ dotfiles_shown ^ paths_shown) && event == Event::Character('b')) {
      screen.ExitLoopClosure()();
      system(conf.file_browser_cmd);
      return true;
    }
    // <enter> select a item
    if (!oldfiles_shown && !dotfiles_shown && !paths_shown && event == Event::Return) {
      radiobox->OnEvent(event);
      switch(conf.radiobox_selected) {
        case 0:
          oldfiles_shown = true;
          break;
        case 1:
          screen.ExitLoopClosure()();
          system(conf.find_file_cmd);
          break;
        case 2:
          screen.ExitLoopClosure()();
          system(conf.file_browser_cmd);
          break;
        case 3:
          dotfiles_shown = true;
          break;
        case 4:
          paths_shown = true;
          break;
        case 5:
          screen.ExitLoopClosure()();
          break;
      }
      return true;
    }
    if (oldfiles_shown && event == Event::Return) {
      oldfiles_box->OnEvent(event);
      oldfiles_shown = false;
      screen.ExitLoopClosure()();
      system((conf.editor + " " + oldfiles_list[conf.oldfiles_selected]).c_str());
      return true;
    }
    if (dotfiles_shown && event == Event::Return) {
      dotfiles_box->OnEvent(event);
      dotfiles_shown = false;
      screen.ExitLoopClosure()();
      system((conf.editor + " " + conf.dotfiles_list[conf.dotfiles_selected]).c_str());
      return true;
    }
    if (paths_shown && event == Event::Return) {
      paths_box->OnEvent(event);
      screen.ExitLoopClosure()();
      paths_shown = false;
      system((std::string("echo cd ") + conf.paths_list[conf.paths_selected] + "> /tmp/startup_cd.sh").c_str());
      return true;
    }
    return false;
  });
  screen.Loop(component);
  // if (paths_shown) {
  //   std::cout << std::string("cd ") + paths_list[paths_selected] << '\n';
  // }
  return EXIT_SUCCESS;
}
