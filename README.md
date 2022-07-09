<br>
<p align="center">
<img alt="logo" src="https://gitee.com/svegeta/screenshot/raw/master/startuplogo-removebg.png" width="50%" />
</p>

<!-- <h1 align="center">StartUp</h1> -->
<h3 align="center">
  A collection of human friendly terminal user interface.
</h3>


<p align="center">
    <a href="#"><img src="https://img.shields.io/badge/c++-%2300599C.svg?style=flat&logo=c%2B%2B&logoColor=white"></img></a>
  <a href="https://github.com/StubbornVegeta/StartUp/blob/master/LICENSE">
    <img src="https://img.shields.io/github/license/StubbornVegeta/StartUp" alt="LICENSE">
  </a>
</p>

<p align="center">
  <a href="#Screenshot"><b>Screenshot</b></a>&nbsp;&bull;
  <a href="#Installation"><b>Installation</b></a>&nbsp;&bull;
  <a href="#Usage"><b>Usage</b></a>&nbsp;&bull;
  <a href="#Configuration"><b>Configuration</b></a>&nbsp;&bull;
  <a href="#Thanks"><b>Thanks</b></a>
</p>

### Screenshot

![](https://gitee.com/svegeta/screenshot/raw/master/StartUp.jpg)

![](https://gitee.com/svegeta/screenshot/raw/master/dotfiles.jpg)

**Note**:

`find file` relies on `fzf`.

`file browser` relies on `ranger` / `lf` / ...

**TODO List**:
- [ ] built-in find file
- [ ] add tmenu (run command)

### Installation 
```bash
git clone https://github.com/StubbornVegeta/StartUp ~/.config/
cd ~/.config/StartUp
./install.sh
```

### Usage
```bash
. $HOME/.config/StartUp/StartUp.sh
```

Or write the following configuration into `~/.zshrc`:
```bash
alias sp='. $HOME/.config/StartUp/StartUp.sh'
```
### Configuration
`config.lua`
```lua
style = "ghost"

dotfiles_list = {
  "~/.zshrc",
  "~/.tmux.conf",
  "~/.config/nvim/init.lua",
  "~/.config/ranger/rc.conf",
  "~/.config/zsh/module/aliases.zsh",
  "~/.config/StartUp/src/config.hpp",
  "~/.config/StartUp/config.lua",
  "~/.config/StartUp/header/header.lua",
}

paths_list = {
  "~/.config/StartUp",
  "~/.config/StartUp/src",
  "~/.config/StartUp/build",
  "~/.config",
  "~/.config/nvim",
  "~/.config/ranger",
  "~/.config/zsh/module",
}

radiobox_selected   = 0
oldfiles_selected   = 0
dotfiles_selected   = 0
paths_selected      = 0

editor              = "nvim"
file_browser_cmd    = "ranger"
find_file_cmd       = "nvim $(fzf)"
oldfiles_cmd        = "nvim --headless -u NONE -c'echo v:oldfiles | qall!' 2>&1"

url                 = "https://github.com/StubbornVegeta/StartUp"
```
`style` ( logo style ):
 - `ghost`
 - `melting`
 - `fading`
 - `hand_writing`
 - `black_outline`

### Thanks
- [dashboard-nvim](https://github.com/glepnir/dashboard-nvim) - UI Reference
- [FTXUI](https://github.com/ArthurSonzogni/FTXUI)  - TUI
