/* main.cpp: Main file of CTris
 * 
 * Developed by Mitchel Paulin <Mitchel0022@gmail.com>
 * 
 * Date of last modification: 22/02/2021
 */

#include <iostream>
#include <cstring>
#include <curses.h>
#include <vector>
#include <unistd.h>
#include <random>
#include <locale.h>
#include <config.h>
#include "../include/border_window.h"
#include "../include/game_window.h"
#include "../include/constants.h"
#include "../include/all_blocks.h"
#include "../include/ctris.h"

int main(int argc, char **argv)
{
    if(argc == 2){
        if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")){
            std::cout << VERSION << std::endl;
            puts(HELP);
        }
        else if(!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")){
            std::cout << argv[0] << " " << VERSION << std::endl;
        }
        else if(!strcmp(argv[1], "--license")){
            std::cout << LICENSE << std::endl;
        }
        else if(!strcmp(argv[1], "-dev") || !strcmp(argv[1], "--developers")){
            std::cout << DEV_INFO << std::endl;
        }
    }
    else if(argc == 1){
        setlocale(LC_CTYPE, ""); //allow unicode characters
        initscr();
        cbreak(); //disable buffering
        start_color(); //enable colors
        initColors();
        noecho();
        curs_set(FALSE); //hide cursor

        //Initialize random number generator
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, BLOCK_TYPES);

        //Construct windows
        BorderWindow UIWindow = BorderWindow(HEIGHT, WIDTH, GAME_WIDTH, 0);
        GameWindow gameWindow = GameWindow(HEIGHT, GAME_WIDTH, 0, 0);
        keypad(UIWindow.getWin(), TRUE); //enable keypad inputs from user
        gameWindow.render();

        //Prevent wgetch from being a blocking call
        nodelay(UIWindow.getWin(), TRUE);

        //Create the two initial pieces
        Block *curPiece = createNewBlock(dist6(rng));
        Block *nextPiece = createNewBlock(dist6(rng));
        UIWindow.addNextBlock(*nextPiece);

        int score = 0;
        int downTimer = 0; //Once this hits a certain number of loops we move the block down
        int userInput;
        bool gameOver = false;

        //Game loop
        for (;;)
        {
            usleep(CLOCK_SPEED);
            
            //Process user input
            userInput = wgetch(UIWindow.getWin());

            //Check for control inputs 
            if (userInput == 'r' || userInput == 'R')
            {
                //Reset game
                delete (curPiece);
                delete (nextPiece);
                curPiece = createNewBlock(dist6(rng));
                nextPiece = createNewBlock(dist6(rng));
                score = 0;
                gameWindow.initWindow();
                UIWindow.initWindow();
                UIWindow.addNextBlock(*nextPiece);
                gameOver = false;
                continue;
            }
            else if (userInput == EXIT_KEY)
            {
                break; // exit
            }

            if (gameOver)
            {
                continue;
            }

            //Erase block so we can redraw it in new location
            gameWindow.eraseBlock(*curPiece);

            //Check for block movement inputs 
            if (userInput == 'd' || userInput == 'D' || userInput == KEY_RIGHT)
            {
                if (canMoveRight(*curPiece, gameWindow))
                {
                    curPiece->moveRight();
                }
            }
            else if (userInput == 'a' || userInput == 'A' || userInput == KEY_LEFT)
            {
                if (canMoveLeft(*curPiece, gameWindow))
                {
                    curPiece->moveLeft();
                }
            }
            else if (userInput == 'w' || userInput == 'W' || userInput == KEY_UP)
            {
                Block *rotatedPiece = curPiece->rotate();
                //If we can rotate the piece
                if (!gameWindow.blockCollides(*rotatedPiece))
                {
                    gameWindow.eraseBlock(*curPiece);
                    delete (curPiece);
                    curPiece = rotatedPiece;
                }
                else //Could not rotate piece
                {
                    delete (rotatedPiece);
                }
            }
            else if (userInput == 's' || userInput == 'S' || userInput == KEY_DOWN)
            {
                if (canMoveDown(*curPiece, gameWindow))
                {
                    curPiece->moveDown();
                    downTimer = 0; //Reset down timer
                }
            }
            else if (userInput == ' ') //spacebar pressed
            {
                while (canMoveDown(*curPiece, gameWindow))
                {
                    curPiece->moveDown();
                }
                downTimer = BLOCK_FALL_SPEED; //block reached bottom, force spawn
            }

            //Move block down
            if (downTimer > BLOCK_FALL_SPEED)
            {
                if (canMoveDown(*curPiece, gameWindow))
                {
                    curPiece->moveDown();
                    downTimer = 0;
                }
                else
                {
                    //Piece reached bottom, check if player looses
                    //If any block is still "in play" then continue
                    bool lost = true;
                    for (Square *s : curPiece->getSquares())
                    {
                        if (s->getRow() < BOARD_TOP - 2)
                        {
                            lost = false;
                        }
                    }

                    if (lost)
                    {
                        gameWindow.fillScreen();
                        gameWindow.render();
                        gameOver = true;
                        continue;
                    }

                    gameWindow.drawBlock(*curPiece);

                    //check if we need to remove any lines first
                    int lines = gameWindow.removeCompletedLines();

                    //update score
                    if (lines > 0)
                    {
                        score += linesToScore(lines);
                        UIWindow.updateScore(score);
                    }

                    //setup for next block
                    delete (curPiece);
                    curPiece = nextPiece;
                    nextPiece = createNewBlock(dist6(rng));
                    UIWindow.addNextBlock(*nextPiece);
                    continue;
                }
            }
            else
            {
                downTimer++;
            }

            //re render screen with new block location
            gameWindow.drawBlock(*curPiece);
            gameWindow.render();
        }

        //Exit game
        delete (curPiece);
        delete (nextPiece);
        endwin();
    }
    else{
        std::cerr << "\033[1;31mE:\033[m \033[1mInvalid arguments!\033[m" << std::endl;
        std::cerr << "Please see " << argv[0] << " -h for help" << std::endl;
        return 1;
    }
	return 0;
}

/*
	Returns a new tetris block 
*/
Block *createNewBlock(int num)
{
	switch (num)
	{
	case 1:
		return new LLeftPiece();
	case 2:
		return new LRightPiece();
	case 3:
		return new LongPiece();
	case 4:
		return new SnakeLeftPiece();
	case 5:
		return new SnakeRightPiece();
	case 6:
		return new SquarePiece();
	case 7:
		return new TPiece();
	default:
		return new TPiece();
	}
}

/*
	Returns the score awarded for clearing a particular number of lines 
	Uses the Original BPS scoring system (https://tetris.wiki/Scoring)
*/
int linesToScore(int lines)
{
	switch (lines)
	{
	case 1:
		return 40;
	case 2:
		return 100;
	case 3:
		return 300;
	case 4:
		return 1200;
	default:
		return 0;
	}
}

/*
	Determin if, given the current block, whether or not we can move right 
*/
bool canMoveRight(Block block, GameWindow &win)
{
	for (Square *s : block.getSquares())
	{
		if (s->getCol() == BOARD_WIDTH - 1 || !win.isCellEmpty(s->getRow(), s->getCol() + 1))
		{
			return false;
		}
	}
	return true;
}

/*
	Determine if, given the current block, whether or not we can move left
*/
bool canMoveLeft(Block block, GameWindow &win)
{
	for (Square *s : block.getSquares())
	{
		if (s->getCol() <= 0 || !win.isCellEmpty(s->getRow(), s->getCol() - 1))
		{
			return false;
		}
	}
	return true;
}

/*
	Determine if, given the current block, whether or not we can move down
*/
bool canMoveDown(Block block, GameWindow &win)
{
	for (Square *s : block.getSquares())
	{
		if (s->getRow() <= 0 || !win.isCellEmpty(s->getRow() - 1, s->getCol()))
		{
			return false;
		}
	}
	return true;
}

/*
	Create all colors pairs for use later 
*/
void initColors()
{
	for (int i = COLOR_BLACK; i <= COLOR_WHITE; i++)
	{
		init_pair(i, i, i);
	}
}
