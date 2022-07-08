# StartUp

![](https://gitee.com/svegeta/screenshot/raw/master/StartUp.jpg)

![](https://gitee.com/svegeta/screenshot/raw/master/dotfiles.jpg)

**Note**:

`find file` relies on `fzf`.

`file browser` relies on `ranger` / `lf` / ...

**TODO List**:
- [ ] built-in find file
- [ ] add tmenu (run command)

### Install 
```bash
git clone https://github.com/StubbornVegeta/StartUp > ~/.config/
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

