/* ctris.h: Contain the informations about this software
 * 
 * Developed by Gustavo Bacagine <gustavo.bacagine@protonmai.com>
 * 
 * Date: 18/02/2021
 * Date of last modification: 22/02/2021
 */

#ifndef _CTRIS_H
#define _CTRIS_H

#define HELP    "Mitchel Paulin (C) 2020 - 2021.\n\
Released under the MIT License.\n\n\
CTris is a command line Tetris program written in C++. Made \n\
to work in the standard 80x24 terminal of most linux\n\
systems. Also works pretty well on the Windows Linux\n\
subsystem. Implemented custom rendering, collision detection\n\
and rotation algorithms.\n\
\n\
Arguments:\n\
  -h, --help\t\tShow this message and exit\n\
  -v, --version\t\tShow version and exit\n\
  --license\t\tShow the license and exit\n\
  -dev, --developers\tShow developers information and exit"
#define DEV_INFO "This program is created by Mitchel Paulin <Mitchel0022@gmail.com>\n\
and modifyed by Gustavo Bacagine <gustavo.bacagine@protonmail.com>"
#define LICENSE "MIT License\n\
\n\
Copyright (c) 2020 Mitchel Paulin\n\
\n\
Permission is hereby granted, free of charge, to any person obtaining a copy\n\
of this software and associated documentation files (the \"Software\"), to deal\n\
in the Software without restriction, including without limitation the rights\n\
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n\
copies of the Software, and to permit persons to whom the Software is\n\
furnished to do so, subject to the following conditions:\n\
\n\
The above copyright notice and this permission notice shall be included in all\n\
copies or substantial portions of the Software.\n\
\n\
THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n\
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n\
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n\
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n\
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n\
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n\
SOFTWARE."

/*  */
void initColors();

/*  */
bool canMoveRight(Block block, GameWindow &win);

/*  */
bool canMoveLeft(Block block, GameWindow &win);

/*  */
bool canMoveDown(Block block, GameWindow &win);

/*  */
Block *createNewBlock(int num);

/*  */
int linesToScore(int lines);

#endif
