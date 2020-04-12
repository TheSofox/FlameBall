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
};

struct Ball{
	struct Vector2 ppos;
	struct Vector2f pos;
	struct Vector2f vel;
	int pauseTime;
	int offside;
};

struct GameState{
	int p1s;
	int p2s;
	int serve;
	int screen;
};



#endif // _GLOBAL_H_