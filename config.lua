style = "ghost"

keymap = {
	["history_files"] = "<C-h>",
	["find_file"] = "<C-f>",
	["file_browser"] = "<C-b>",
	["open_dotfiles"] = "<C-d>",
	["tag_paths"] = "<C-t>",
	["exit"] = "<Esc>",
	["select_next"] = "<C-n>",
	["select_prev"] = "<C-p>",
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
	"~/svegeta",
}

radiobox_selected = 0
oldfiles_selected = 0
dotfiles_selected = 0
paths_selected = 0

editor = "nvim"
file_browser_cmd = "ranger"
find_file_cmd = "nvim $(fzf)"
oldfiles_cmd = "nvim --headless -u NONE -c'echo v:oldfiles | qall!' 2>&1"

url = "https://github.com/Kurama622/StartUp"
