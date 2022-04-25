# HV
Ok little fuckers ~~haha yes joke~~, you wanna go to your favourite _ahem "educational webpage"_, and do not wanna be traced? Well, now you can! With HV (For **H**entai **V**iewer)!

Note: HV expects a tor server to be running if you've not specified the `-p or -c` option
# Dependencies
Ubuntu
```
sudo apt install libgtkmm-3.0-dev libwebkit2gtk-4.0-dev
```
Arch Linux
```
sudo pacman -S gtkmm3 webkit2gtk
```

# Compiling
```
git clone https://github.com/RadioMetronome/HV
cd HV
make
```

# Usage
By default the page that will be opened is <a href=https://rule34.xxx> this one (Warning: NSFW!)</a> but it can be changed <br>
With `hv <url>` you can open a different page. Even duckduckgo! <br>
**¿Not happy with the default window size?**
<br>Run `hv -s width height`!
<br>**¿Is TOR too slow for you?**
<br>You can run it with ProtonVPN (`hv -p`) or no VPN at all (`hv -c`)
