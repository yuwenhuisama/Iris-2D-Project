#ifndef _H_GAMERESOURCE_
#define _H_GAMERESOURCE_

#define GAME_TITLE  L"Simple Iris 2D Flappy Bird Demo"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

#define MAP_WIDTH 600
#define MAP_HEIGHT 400

#define MID_HEIGHT 90
#define PIPE_WIDTH 52
#define MIN_PIPE_HEIGHT 50
#define MAX_PIPE_HEIGHT (MAP_HEIGHT - MID_HEIGHT - MIN_PIPE_HEIGHT)
#define OTHER_PIPE_HEIGHT(ch) (MAP_HEIGHT - ch - MID_HEIGHT)

#define FIRST_PIPE_X 100
#define SECOND_PIPE_X 400

#define FONT_WIDTH 40
#define FONT_HEIGHT 60

#define POINT_FONT_NAME L"ºÚÌå"

#define IMAGE_BACKGROUND L"image\\Background.png"
#define IMAGE_GROUND L"image\\Ground.png"
#define IMAGE_HINT L"image\\Hint.png"
#define IMAGE_BIRD L"image\\Birds.png"
#define IMAGE_PIPE_TOP L"image\\Pipe_Top.png"
#define IMAGE_PIPE_BOTTOM L"image\\Pipe_Bottom.png"
#define IMAGE_SCOREBOARD L"image\\ScoreBoard.png"
#define IMAGE_BUTTONS L"image\\Buttons.png"
#define IMAGE_SCOREFONT L"image\\ScoreFont.png"

#define POINT_FILE_NAME L"maxpoint.dat"

#define MESSAGE_TITLE L"Hello!"
#define MESSAGE_CONTENT L"Hey! Don't you think this is a good demo?"

#endif