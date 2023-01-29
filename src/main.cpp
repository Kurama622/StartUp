#include "modal.hpp"
#include "config.hpp"

#include "base.hpp"
#include "ui.hpp"
#include "keymap.hpp"

using namespace ftxui;
using namespace StartUp;


int main(void) {
  ScreenInteractive screen = ScreenInteractive::Fullscreen();
  UI ui = StartUp::InitUI();
  Component component = CatchEvent(ui.main_container, [&](Event event) {
                                return KeyCallback(screen, ui, event);
                              });
  screen.Loop(component);
  return EXIT_SUCCESS;
}
