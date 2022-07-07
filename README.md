## StartUp
![](https://gitee.com/svegeta/screenshot/raw/master/StartUp.jpg)

![](https://gitee.com/svegeta/screenshot/raw/master/dotfiles.jpg)

### Install 
```bash
git clone https://github.com/StubbornVegeta/StartUp > ~/.config/
cd ~/.config/StartUp
mkdir build
cd build
cmake ..
make
sudo cp StartUp /usr/local/bin/ 
```

### Usage
```bash
. $HOME/.config/StartUp/StartUp.sh
```

Or write the following configuration into `~/.zshrc`:
```bash
alias sp='. $HOME/.config/StartUp/StartUp.sh'
```

