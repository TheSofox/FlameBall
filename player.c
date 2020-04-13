#include "player.h"
#include "constants.h"

struct Player initPlayer(int pno){
	struct Player player;
	player.swing = 0;
	player.anim = 0;
	player.score = 0;
	player.hitFrame = FALSE;
	if(pno==1){
		player.pos.x=0;
	} else {
		player.pos.x=SCREEN_WIDTH-40;
	}
	player.pos.y = SCREEN_MIDDLE;
	player.vel.x = 0;
	player.vel.y = 0;
	return player;
}


struct Player updatePlayer(struct Player player, u16 input){
	int yDir = 0;
	if(input & BUTTON_UP) yDir = -1;
	else if(input & BUTTON_DOWN) yDir = 1;
	int xDir = 0;
	//if(input & BUTTON_LEFT) xDir = -1;
	//else if(input & BUTTON_RIGHT) xDir = 1;
	
	player.vel.y += 0.3f * yDir;
	
	player.vel.y*= 0.9;
	if (abs(player.vel.y)<=0.000001)
		player.vel.y = 0;
	player.pos.y += player.vel.y;
	
    
	
	if(player.pos.y<0){
		player.pos.y = 0;
		player.vel.y = 0;
	}
	if(player.pos.y>SCREEN_HEIGHT-32){
		player.pos.y = SCREEN_HEIGHT-32;
		player.vel.y = 0;
	}
	player.pos.x += xDir;
	
	
	if((input & BUTTON_A) && !(player.lastInput & BUTTON_A)){
		player.swing = SWING_TIME;
		player.hitFrame = TRUE;
	} else {
		player.hitFrame = FALSE;
	}
	player.anim = (input & BUTTON_A)? 1 : 0;
	
	player.ppos.x = player.pos.x;
	player.ppos.y = player.pos.y;
	
	player.lastInput = input;
	return player;
}
struct Player player_add_score(struct Player player){
	player.score++;
	return player;
}
struct Player player_set_winner(struct Player player){
    player.anim = 2;
	return player;
}
struct Player player_set_loser(struct Player player){
    player.anim = 3;
	return player;
}