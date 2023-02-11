-- style = "ghost"
style = "hydra"

history_files_key = "<C-h>"
find_file_key     = "<C-f>"
file_browser_key  = "<C-b>"
open_dotfiles_key = "<C-d>"
tag_paths_key     = "<C-t>"
exit_key          = "<Esc>"

select_next_key   = "<C-n>"
select_prev_key   = "<C-p>"

dotfiles_list = {
  "~/.zshrc",
  "~/.tmux.conf",
  "~/.config/nvim/init.lua",
  "~/.config/ranger/rc.conf",
  "~/.config/zsh/module/aliases.zsh",
  "~/.config/StartUp/src/config.hpp",
  "~/.config/StartUp/config.lua",
  "~/.config/StartUp/header/header.lua",
  "/mnt/c/Users/vegeta/.config/wezterm/wezterm.lua",
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

radiobox_selected   = 0
oldfiles_selected   = 0
dotfiles_selected   = 0
paths_selected      = 0

editor              = "nvim"
file_browser_cmd    = "ranger"
find_file_cmd       = "nvim $(fzf)"
oldfiles_cmd        = "nvim --headless -u NONE -c'echo v:oldfiles | qall!' 2>&1"

url                 = "https://github.com/StubbornVegeta/StartUp"
