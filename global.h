#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <genesis.h>


static const int LEFT_EDGE = 0;
static const int SCREEN_WIDTH = 320;
static const int TOP_EDGE = 0;
static const int SCREEN_HEIGHT = 224;
static const int SCREEN_MIDDLE = 112;

static const int BALL_XO = 4;
static const int BALL_YO = 4;
static const int BALL_HEIGHT = 8;

static const int PLAYER_YO = 16;
static const int PLAYER_HEIGHT = 32;


static const int SWING_COOLDOWN = 0;
static const int SWING_TIME = 10;


struct Vector2f{
	float x;
	float y;
};

struct Vector2{
	int x;
	int y;
};
struct PadInput{
	int yDir;
};

struct Player{
	struct Vector2 ppos;
	struct Vector2f pos;
	struct Vector2f vel;
	int swing;
	bool hitFrame;
	int anim;
	u16 lastInput;
};

struct Ball{
	struct Vector2 ppos;
	struct Vector2f pos;
	struct Vector2f vel;
	int offside;
};

struct GameState{
	int p1s;
	int p2s;
	int serve;
};



#endif // _GLOBAL_H_