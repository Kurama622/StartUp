#ifndef _STARTUP_UI
#define _STARTUP_UI

#include "ftxui/component/component.hpp"           // for Radiobox
#include <vector>
#include "base.hpp"
#include "config.hpp"

namespace StartUp {
  using namespace ftxui;

  struct UI {
    Component main_container;
    Component options_box;
    Component history_files_input_box;
    Component dotfiles_input_box;
    Component paths_input_box;
    Component history_files_box;
    Component dotfiles_box;
    Component paths_box;
    std::vector<std::string>& history_files_list_bak;
    std::vector<std::string>& dotfiles_list_bak;
    std::vector<std::string>& paths_list_bak;
  };

  // struct SeaPreComponent {
  //   Component box;
  //   Component renderer;
  // };

  extern startup conf;

  Component Dashboard(Elements elements, Component radiobox);

  inline Component ModalComponent(std::function<void()> do_nothing,
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
    return component;
  }

  // State of the application:
  extern bool history_files_shown;
  extern bool dotfiles_shown;
  extern bool paths_shown;
  UI InitUI();

  Element SearchPreviewRenderer(std::string& file_name,
                                  std::string& file_name_bak,
                                  std::vector<std::string>& list,
                                  std::vector<std::string>& list_bak,
                                  int& selected,
                                  Component& input_box,
                                  Component& box,
                                  const std::string& model_name,
                                  int list_win_h_per,
                                  int preview_win_h_per,
                                  int w_per,
                                  bool is_preview);







  // void SearchPreviewComponent(std::vector<std::string>& list,
  //                             std::vector<std::string>& list_bak,
  //                             int& selected,
  //                             Component& box,
  //                             Component& render,
  //                             const char* model_name,
  //                             int list_win_h_per,
  //                             int preview_win_h_per,
  //                             int w_per);
}
#endif //_STARTUP_UI
