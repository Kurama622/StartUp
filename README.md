<br>
<p align="center">
<img alt="logo" src="https://gitee.com/kurama622/screenshot/raw/master/startuplogo-removebg.png" width="50%" />
</p>

<!-- <h1 align="center">StartUp</h1> -->
<h3 align="center">
  A collection of human friendly terminal user interface.
</h3>


<p align="center">
    <a href="#"><img src="https://img.shields.io/badge/c++-%2300599C.svg?style=flat&logo=c%2B%2B&logoColor=white"></img></a>
  <a href="https://github.com/kurama622/StartUp/blob/master/LICENSE">
    <img src="https://img.shields.io/github/license/kurama622/StartUp" alt="LICENSE">
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

![](https://i-blog.csdnimg.cn/direct/796ebba2008749818f76ccd39ba17719.png)

![](https://i-blog.csdnimg.cn/direct/0c1e2e19b8c448f294b315d8ac140770.png)

#### history files preview
![](https://img-blog.csdnimg.cn/img_convert/539918ba6d91c4f18db7c72f55255f0e.png)

**Note**:

`find file` relies on `fzf`.

`file browser` relies on `ranger` / `lf` / ...


### Installation 
```bash
git clone https://github.com/Kurama622/StartUp ~/.config/
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
#### Keymap

| keymap          | Action                     |
|-----------------|----------------------------|
| `TAB`           | select the next option     |
| `Shift` + `TAB` | select the previous option |
| `Enter`         | confirm the option         |

You can also customize your shortcuts, such as:

```lua
select_next_key   = "<C-n>"
select_prev_key   = "<C-p>"
```

### Configuration
`config.lua`
```lua
style = "ghost"

keymap = {
  ["history_files"] = "<C-h>",
  ["find_file"]     = "<C-f>",
  ["file_browser"]  = "<C-b>",
  ["open_dotfiles"] = "<C-d>",
  ["tag_paths"]     = "<C-t>",
  ["exit"]          = "<Esc>",
  ["select_next"]   = "<C-n>",
  ["select_prev"]   = "<C-p>"
}

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
  "~/Desktop",
  "~/svegeta"
}

-- The first option is selected by default
radiobox_selected   = 0
oldfiles_selected   = 0
dotfiles_selected   = 0
paths_selected      = 0

editor              = "nvim"
file_browser_cmd    = "ranger"
find_file_cmd       = "nvim $(fzf)"
oldfiles_cmd        = "nvim --headless -u NONE -c'echo v:oldfiles | qall!' 2>&1"

url                 = "https://github.com/Kurama622/StartUp"

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
