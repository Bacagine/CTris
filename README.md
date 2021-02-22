# CTris 
[![ctris](https://snapcraft.io//ctris/badge.svg)](https://snapcraft.io/ctris)

[CTris](https://snapcraft.io/ctris) is a command line Tetris program written in C++. Made to work in the standard 80x24 terminal of most linux systems. Also works pretty well on the Windows Linux subsystem. Implemented custom rendering, collision detection and rotation algorithms.

You can install ctris directly from the snap store!
>sudo snap install ctris

![demo](demo/demo.png)
![gameover](demo/demo_gameover.png)

# Dependencies 

Install the ncurses lib
`sudo apt-get install libncurses5-dev libncursesw5-dev`

ncurses is a barebones API that allows you to write text-based user interfaces in a terminal-independent manner.

# Build and install
Run:

`./autogen.sh`

`./configure --prefix=/usr --mandir=/usr/share/man --docdir=/usr/share/doc`

`make && sudo make install`

# Generate a .deb package and install

`git clone https://github.com/Bacagine/CTris.git ctris`

`cd ctris`

`./autogen.sh`

`./configure --prefix=/usr --mandir=/usr/share/man --docdir=/usr/share/doc`

`make`

`mkdir -p /tmp/ctris/DEBIAN`

`cp control /tmp/ctris/DEBIAN`

`make install DESTDIR=/tmp/ctris`

`dpkg-deb /tmp/goodbye /tmp/ctris.deb`

`apt-get install /tmp/ctris.deb`
