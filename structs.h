#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <genesis.h>

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
	int score;
};

struct Ball{
	struct Vector2 ppos;
	struct Vector2f pos;
	struct Vector2f vel;
	int pauseTime;
	int offside;
	bool justHit;
};

struct GameState{
	int serve;
	int screen;
	bool winScreen;
};



#endif // _GLOBAL_H_