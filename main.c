#include <genesis.h>
#include <resources.h>

#include "structs.h"
#include "ball.h"
#include "constants.h"


Sprite* ballSprite;
Sprite* player1Sprite;
Sprite* player2Sprite;






void drawInt( u32 nb, u8 x, u8 y, u8 zeros )
{
	s8 str [ zeros+1 ];
	intToStr ( nb, str, zeros );

	SYS_disableInts();
	VDP_drawText ( str, x, y );
	SYS_enableInts();
}

void drawUInt( u32 nb, u8 x, u8 y, u8 zeros )
{
	s8 str [ zeros+1 ];
	uintToStr ( nb, str, zeros );

	SYS_disableInts();
	VDP_drawText ( str, x, y );
	SYS_enableInts();
}





struct Player initPlayer(int pno){
	struct Player player;
	player.swing = 0;
	player.anim = 0;
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


struct GameState screen_to_title(struct GameState gameState){
	gameState.screen = 1;

	//VDP_setPalette(PAL1, imglogo.palette->data);
	VDP_drawImageEx(BG_A, &imglogo, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), 4, 1, 0, CPU);
	
	//VDP_drawText("FlameBall!", 10, 1);
	
	VDP_drawText("Press to Start!", 12, 14);

	VDP_drawText("(c) Sofox 2020", 21, 27);

	return gameState;
}
struct GameState screen_to_game(struct GameState gameState){
	gameState.screen = 2;
	gameState.p1s = 0;
	gameState.p2s = 0;
	gameState.serve = 1;

	
	VDP_setPalette(PAL1, imgball.palette->data);
	VDP_setPalette(PAL2, imgplayer.palette->data);
	VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x704320));

	//VDP_setPlanSize(32,32);
	VDP_loadTileSet(imgcave.tileset,1,DMA);
	VDP_setPalette(PAL3, imgcave.palette->data);
	VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL3,0,FALSE,FALSE,1),0,0,40,28);
	//VDP_fillTileMapRectInc(BG_A,TILE_ATTR_FULL(PAL3,0,FALSE,FALSE,3),0,0,10,10);
	VDP_drawText("FlameBall Tournament!", 10, 1);


	return gameState;
}
struct GameState initGame(){
	struct GameState gameState;
	return screen_to_title(gameState);
}

int main(){
	JOY_init();
	

	SPR_init(0,0,0);
	
	struct Ball ball = initBall(1);
	struct Player player1 = initPlayer(1);
	struct Player player2 = initPlayer(2);
	
	struct GameState gameState = initGame();




	
	ballSprite = SPR_addSprite(&imgball,-64,100,TILE_ATTR(PAL1,0, FALSE, FALSE));
	
	player1Sprite = SPR_addSprite(&imgplayer,-64,100,TILE_ATTR(PAL2,0, FALSE, TRUE));
	player2Sprite = SPR_addSprite(&imgplayer,-64,100,TILE_ATTR(PAL2,0, FALSE, FALSE));
	u16 joyInput1;
	u16 joyInput2;
	


	while(1)
	{
		if(gameState.screen == 1){
			if(JOY_readJoypad(JOY_1) & BUTTON_START){
				gameState = screen_to_game(gameState);
			}
			if(JOY_readJoypad(JOY_2) & BUTTON_START){
				gameState = screen_to_game(gameState);
			}
			
		}
		if(gameState.screen == 2){
			joyInput1 = JOY_readJoypad(JOY_1);
			player1 = updatePlayer(player1, joyInput1);
			joyInput2 = JOY_readJoypad(JOY_2);
			player2 = updatePlayer(player2, joyInput2);
			
			//VDP_drawText(3, 1, 2);
			drawInt(gameState.p1s,18,2,1);
			drawInt(gameState.p2s,22,2,1);
			
			ball = updateBall(ball, player1, player2);
			
			if(ball.offside!=0){
				if(ball.offside<0){
					gameState.p1s+=1;
					gameState.serve = -1;
				}
				if(ball.offside>0){
					gameState.p2s+=1;
					gameState.serve = 1;
				}

				ball = initBall(gameState.serve);
				//int t = true ? 1:3;
			}
			if(ball.pauseTime>0){
				VDP_drawText("Ready?", 17, 12);
			} else {	
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL3,0,FALSE,FALSE,1),17,12,6,1);
			}
			
			SPR_setHFlip (ballSprite, ball.vel.x>0);
			SPR_setPosition(ballSprite, ball.ppos.x,ball.ppos.y);
			
			SPR_setPosition(player1Sprite, player1.ppos.x,player1.ppos.y);
			SPR_setAnim(player1Sprite, player1.anim ); 
			SPR_setPosition(player2Sprite, player2.ppos.x,player2.ppos.y);
			SPR_setAnim(player2Sprite, player2.anim ); 
		}
		


		SPR_update();
		VDP_waitVSync();
	}
	return (0);
}
