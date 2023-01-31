#include "ftxui/screen/string.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/component/event.hpp"               // for Event
#include "unistd.h"
#include <algorithm>
#include <iostream>

#include "modal.hpp"
#include "config.hpp"

#include "base.hpp"
#include "ui.hpp"

namespace StartUp {
  using namespace ftxui;
  startup conf = setup();
  bool history_files_shown = false;
  bool dotfiles_shown = false;
  bool paths_shown    = false;
  Component Dashboard(Elements elements, Component radiobox) {
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
    });
  }

  // search and preview component
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
                                  bool is_preview) {
      if (file_name != file_name_bak) {
        file_name_bak = file_name;
        list_bak.clear();
        selected = 0;
        filter(list, list_bak, file_name);
        if (file_name.empty() && list_bak.empty()) {
           list_bak = list;
        }
      }
      static Elements con = {};
      if (!list_bak.empty()) {
        con = PreviewContent(list_bak, selected, model_name);
      }

      return vbox({
                  vbox({
                    hbox({color(Color::Cyan, text("  ")) | blink,
                                  hbox(input_box->Render()) }),
                  }),
                  separator() | color(Color::Green),
                  vbox({
                    window(text(model_name) | hcenter,
                           vbox(color(Color::Cyan, box->Render()))
                           | yframe)
                    | size(HEIGHT, EQUAL, list_win_h_per)
                    | size(WIDTH, EQUAL, w_per)
                    | color(Color::Green),

                    is_preview ?
                    window(text(" PREVIEW ") | hcenter,
                           color(Color::Cyan, vbox(con)))
                    | size(HEIGHT, EQUAL, preview_win_h_per)
                    | size(WIDTH, EQUAL, w_per)
                    | color(Color::Green)
                    :text("")
                   })
                });
    }
  
  // void SearchPreviewComponent(std::vector<std::string>& list,
  //                                  std::vector<std::string>& list_bak,
  //                                  int& selected,
  //                                  Component& box,
  //                                  Component& renderer,
  //                                  const char* model_name,
  //                                  int list_win_h_per,
  //                                  int preview_win_h_per,
  //                                  int w_per) {
  //   static std::string file_name;
  //   static std::string file_name_bak;
  //   file_name_bak = file_name;
  //   static Component input_box;
  //   input_box = Input(&file_name, "") | color(Color::White);

  //   // static Component list_box;
  //   box = Menu(&list_bak, &selected);

  //   static Component container;
  //   container = Container::Vertical({
  //       input_box,
  //       box,
  //   });

  //   // static Component renderer;
  //   renderer = Renderer(container, [&] {

  //                       });
  // }


  UI InitUI() {
    // initialize logo
    static Elements logo;
    for (const std::string& it : conf.header) {
      logo.push_back(color(Color::Green, text(it)));
    }

    // initialize actionable options
    // static auto options_box = Radiobox(&conf.item_show, &conf.radiobox_selected);
    static auto options_box = Menu(&conf.item_show, &conf.radiobox_selected);

    static Component main_container = Container::Horizontal({
        Dashboard(logo, options_box) | flex,
    });

    // history_files
    static std::vector<std::string> history_files_list = HistoryFiles(conf.history_files_cmd);
    static std::vector<std::string> history_files_list_bak = history_files_list;
    static std::string history_file_name;
    static std::string history_file_name_bak = history_file_name;
    static Component history_file_input_box = Input(&history_file_name, "") | color(Color::White);
    // static Component history_files_box;
    static Component history_files_box = Menu(&history_files_list_bak, &conf.history_files_selected);
    static Component history_files_container = Container::Vertical({
        history_file_input_box,
        history_files_box,
    });
    // static Component history_files_renderer;

    static Component history_files_renderer = Renderer(history_files_container,
                                                       [&] { return SearchPreviewRenderer(history_file_name,
                                                                                 history_file_name_bak,
                                                                                 history_files_list,
                                                                                 history_files_list_bak,
                                                                                 conf.history_files_selected,
                                                                                 history_file_input_box,
                                                                                 history_files_box,
                                                                                 " HISTORY FILES ",
                                                                                 28, 52, 90, true);
                                                       });

    // dotfiles
    static std::vector<std::string> dotfiles_list_bak = conf.dotfiles_list;
    static std::string dotfiles_name;
    static std::string dotfiles_name_bak = dotfiles_name;
    static Component dotfiles_input_box = Input(&dotfiles_name, "") | color(Color::White);
    static auto dotfiles_box = Menu(&dotfiles_list_bak, &conf.dotfiles_selected);
    static Component dotfiles_container = Container::Vertical({
        dotfiles_input_box,
        dotfiles_box,
    });
    static Component dotfiles_renderer = Renderer(dotfiles_container,
                                                  [&] { return SearchPreviewRenderer(dotfiles_name,
                                                                             dotfiles_name_bak,
                                                                             conf.dotfiles_list,
                                                                             dotfiles_list_bak,
                                                                             conf.dotfiles_selected,
                                                                             dotfiles_input_box,
                                                                             dotfiles_box,
                                                                             " DOT FILES ",
                                                                             conf.dotfiles_list.size()+2, 52, 70, false);
                                                       });

    // tag paths
    static std::vector<std::string> paths_list_bak = conf.paths_list;
    static std::string paths_name;
    static std::string paths_name_bak = paths_name;
    static Component paths_input_box = Input(&paths_name, "") | color(Color::White);
    static auto paths_box = Menu(&paths_list_bak, &conf.paths_selected);
    static Component paths_container = Container::Vertical({
        paths_input_box,
        paths_box,
    });
    static Component paths_renderer = Renderer(paths_container,
                                                  [&] { return SearchPreviewRenderer(paths_name,
                                                                             paths_name_bak,
                                                                             conf.paths_list,
                                                                             paths_list_bak,
                                                                             conf.paths_selected,
                                                                             paths_input_box,
                                                                             paths_box,
                                                                             " TAG PATHS ",
                                                                             conf.paths_list.size()+2, 52, 70, false);
                                                       });
    // SeaPreComponent history_files;

    // SearchPreviewComponent( history_files_list,
    //                         history_files_list_bak,
    //                         conf.history_files_selected,
    //                         history_files_box,
    //                         history_files_renderer,
    //                         "HISTORY FILES",
    //                         28, 52, 90);
    // for (auto i : history_files_list_bak) {
    //   std::cout << i << " ";
    // }

    // static std::string file_name;
    // static std::string file_name_bak = file_name;
    // static Component input_box = Input(&file_name, "") | color(Color::White);

    // static Component history_files_box = Menu(&history_files_list_bak, &conf.history_files_selected);

    // static Component history_files_container = Container::Vertical({
    //     input_box,
    //     history_files_box,
    // });

    // static Component history_files_renderer = Renderer(history_files_container, [&] {
    //   if (file_name != file_name_bak) {
    //     file_name_bak = file_name;
    //     history_files_list_bak.clear();
    //     conf.history_files_selected = 0;
    //     filter(history_files_list, history_files_list_bak, file_name);
    //     if (file_name.empty() && history_files_list_bak.empty()) {
    //        history_files_list_bak = history_files_list;
    //     }
    //   }
    //   static Elements con = {};
    //   if (!history_files_list_bak.empty()) {
    //     con = PreviewContent(history_files_list_bak, conf.history_files_selected);
    //   }

    //   return vbox({
    //               vbox({
    //                 // window(text(""),
    //                 //        hbox({color(Color::Green, text("-> ")) | blink,
    //                 //               hbox(input_box->Render()) }) )
    //                 // | size(HEIGHT, EQUAL, 5),
    //                 hbox({color(Color::Green, text("-> ")) | blink,
    //                               hbox(input_box->Render()) })
    //               }),
    //               separator() | color(Color::Green),
    //               vbox({
    //                 window(text("HISTORY FILES") | hcenter,
    //                        vbox(color(Color::Cyan, history_files_box->Render()))
    //                        | yframe)
    //                 // | size(HEIGHT, LESS_THAN, 38)
    //                 // | size(HEIGHT, GREATER_THAN, 20)
    //                 | size(HEIGHT, EQUAL, 28)
    //                 | size(WIDTH, EQUAL, 90)
    //                 | color(Color::Green),
    //                 window(text("PREVIEW") | hcenter,
    //                        color(Color::Cyan, vbox(con)))
    //                 | size(HEIGHT, EQUAL, 52)
    //                 | size(WIDTH, EQUAL, 90)
    //                 | color(Color::Green),
    //                })
    //             });
    // });

    // static auto dotfiles_box = Menu(&conf.dotfiles_list, &conf.dotfiles_selected);
    // static auto paths_box = Menu(&conf.paths_list, &conf.paths_selected);
    // static auto hide_modal = [&] {
    //                         history_files_shown = false;
    //                         dotfiles_shown = false;
    //                         paths_shown = false;
    //                       };
    // static auto do_nothing = [&] {};
    // static auto dotfiles_component = ModalComponent(do_nothing, hide_modal,
    //                                          dotfiles_box, "Open Dotfiles", 70);
    // static auto paths_component = ModalComponent(do_nothing, hide_modal,
    //                                       paths_box, "Tag Paths", 70);
    main_container |= Modal(history_files_renderer, &history_files_shown);
    main_container |= Modal(dotfiles_renderer, &dotfiles_shown);
    // main_container |= Modal(dotfiles_component, &dotfiles_shown);
    main_container |= Modal(paths_renderer, &paths_shown);
    // main_container |= Modal(paths_component, &paths_shown);
    return {
      main_container,
      options_box,
      history_files_box,
      dotfiles_box,
      paths_box,
      history_files_list_bak,
      dotfiles_list_bak,
      paths_list_bak
    };
  }
}
