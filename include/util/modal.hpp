#include "ftxui/component/component.hpp"

namespace ftxui{
  Component Modal(Component main, Component modal, const bool* show_modal);
  ComponentDecorator Modal(Component modal, const bool* show_modal);
}
