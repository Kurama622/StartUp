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

#include "config.hpp"
#include "modal.hpp"
#include "oldfiles.hpp"

/* using ftxui::Container; */
/* using ftxui::Component; */
/* using ftxui::Elements; */
/* using ftxui::hbox; */
/* using ftxui::vbox; */
/* using ftxui::text; */
/* using ftxui::Color; */
/* using ftxui::center; */
/* using ftxui::vcenter; */
/* using ftxui::hcenter; */
/* using ftxui::flex; */
/* using ftxui::border; */
/* using ftxui::Radiobox; */
/* using ftxui::ScreenInteractive; */
using namespace ftxui;

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
        color(Color::Yellow, text(url)) | center,
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
                    color(Color::CyanLight, dotfiles_box->Render()),
                             }) | yframe;
               })
           | size(WIDTH, GREATER_THAN, percent)
           | border
  });
  // Polish how the two buttons are rendered:
  //
  /* component |= Renderer([&](Element inner ) { */
  /*   return vbox({ */
  /*              inner, */
  /*          })                               // */
  /*          | size(WIDTH, GREATER_THAN, 100)  // */
  /*          | border;                        // */
  /* }); */
  return component;
}


int main(void) {
  auto screen = ScreenInteractive::Fullscreen();
  Elements elements;
  for (const std::string& it : header) {
    elements.push_back(color(Color::Green, text(it)));
  }
  auto radiobox = Radiobox(&radiobox_list, &radiobox_selected);
  auto main_container = Container::Horizontal({
      Document(elements, radiobox) | flex,
  });

  // State of the application:
  bool oldfiles_shown = false;
  bool dotfiles_shown = false;
  bool paths_shown    = false;

  // oldfiles
  std::vector<std::string> oldfiles_list = StartUp::RecentlyOpenFile(oldfiles_cmd);
  auto oldfiles_box = Menu(&oldfiles_list, &oldfiles_selected);
  auto dotfiles_box = Menu(&dotfiles_list, &dotfiles_selected);
  auto paths_box = Menu(&paths_list, &paths_selected);
 

  // Some actions modifying the state:
  /* auto show_oldfiles = [&] { oldfiles_shown = true; }; */
  /* auto show_dotfiles = [&] { dotfiles_shown = true; }; */
  auto hide_modal = [&] { oldfiles_shown = false; dotfiles_shown = false; paths_shown = false;};
  auto do_nothing = [&] {};
  /* auto oldfiles_component = OldFilesComponent(do_nothing, hide_modal, oldfiles_box); */
  auto oldfiles_component = ModalComponent(do_nothing, hide_modal, oldfiles_box, "Recently Open File", 100);
  auto dotfiles_component = ModalComponent(do_nothing, hide_modal, dotfiles_box, "Open Dotfiles", 70);
  auto paths_component = ModalComponent(do_nothing, hide_modal, paths_box, "Tag Paths", 70);
  main_container |= Modal(oldfiles_component, &oldfiles_shown);
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
    if (event == Event::Character('o')) {
      oldfiles_shown = true;
      return true;
    }
    if (event == Event::Character('d')) {
      dotfiles_shown = true;
      return true;
    }
    if (event == Event::Character('p')) {
      paths_shown = true;
      return true;
    }
    if (event == Event::Character('f')) {
      screen.ExitLoopClosure()();
      system(find_file_cmd);
      return true;
    }
    if (event == Event::Character('b')) {
      screen.ExitLoopClosure()();
      system(file_browser_cmd);
      return true;
    }
    if (!oldfiles_shown && !dotfiles_shown && !paths_shown && event == Event::Return) {
      radiobox->OnEvent(event);
      switch(radiobox_selected) {
        case 0:
          oldfiles_shown = true;
          break;
        case 1:
          screen.ExitLoopClosure()();
          system(find_file_cmd);
          break;
        case 2:
          screen.ExitLoopClosure()();
          system(file_browser_cmd);
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
      system((edtior + " " + oldfiles_list[oldfiles_selected]).c_str());
      return true;
    }
    if (dotfiles_shown && event == Event::Return) {
      dotfiles_box->OnEvent(event);
      dotfiles_shown = false;
      screen.ExitLoopClosure()();
      system((edtior + " " + dotfiles_list[dotfiles_selected]).c_str());
      return true;
    }
    if (paths_shown && event == Event::Return) {
      paths_box->OnEvent(event);
      screen.ExitLoopClosure()();
      paths_shown = false;
      system((std::string("echo cd ") + paths_list[paths_selected] + "> $HOME/cd.sh").c_str());
      return true;
    }
    return false;
  });
  screen.Loop(component);
  /* if (paths_shown) { */
  /*   std::cout << std::string("cd ") + paths_list[paths_selected] << '\n'; */
  /* } */
  return EXIT_SUCCESS;
}
