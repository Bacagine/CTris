//the game window wrapper
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "window.h"

class GameWindow : public Window
{

public:
    const static int ROWS = 26; //have some unrendered rows to hold pieces not yet on board
    const static int COLS = 10;
    GameWindow(int width, int height, int startY, int startX);
    void render();
    void initWindow();
    void test();

private:
    short board[ROWS][COLS];
};

#endif
