#include <genesis.h>
#include <resources.h>

#include "structs.h"
#include "ball.h"
#include "player.h"
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
	gameState.serve = 1;
	gameState.winScreen = FALSE;

	
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
	
	SND_startPlay_4PCM_ENV(soundTheme, sizeof(soundTheme), SOUND_PCM_CH2, FALSE);
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
			joyInput2 = JOY_readJoypad(JOY_2);
			if (gameState.winScreen){
				VDP_drawText("Player 0 Wins", 13, 12);
				SPR_setVisibility(ballSprite, HIDDEN);
				if(player1.score>player2.score)
					VDP_drawText("1", 20, 12);
				else
					VDP_drawText("2", 20, 12);
				
				if(joyInput1 & BUTTON_START || joyInput2 & BUTTON_START){
					gameState = screen_to_game(gameState);
					player1 = initPlayer(1);
					player2 = initPlayer(2);
					ball = initBall(1);
					SPR_setVisibility(ballSprite, VISIBLE );
				}

			} else {
				player1 = updatePlayer(player1, joyInput1);
				player2 = updatePlayer(player2, joyInput2);
				
				
				ball = updateBall(ball, player1, player2);
				
				if(player1.hitFrame || player2.hitFrame){
					if(ball.justHit)
						SND_startPlay_4PCM_ENV(soundSwipe, sizeof(soundSwipe), SOUND_PCM_CH2, FALSE);
					else
						SND_startPlay_4PCM_ENV(soundSwoosh, sizeof(soundSwoosh), SOUND_PCM_CH2, FALSE);

				}
				
				if(ball.offside!=0){
					
                    SND_startPlay_4PCM_ENV(soundMiss, sizeof(soundMiss), SOUND_PCM_CH2, FALSE);
					if(ball.offside>0){
						player1 = player_add_score(player1);
						gameState.serve = 1;
						if(player1.score>=SCORE_LIMIT){
							player1 = player_set_winner(player1);
							player2 = player_set_loser(player2);
							gameState.winScreen = TRUE;
							SND_startPlay_4PCM_ENV(soundVictory, sizeof(soundVictory), SOUND_PCM_CH2, FALSE);
						}
					}
					if(ball.offside<0){
						player2 = player_add_score(player2);
						gameState.serve = -1;
						if(player2.score>=SCORE_LIMIT){
							player2 = player_set_winner(player2);
							player1 = player_set_loser(player1);
							gameState.winScreen = TRUE;
							SND_startPlay_4PCM_ENV(soundVictory, sizeof(soundVictory), SOUND_PCM_CH2, FALSE);
						}
					}
					//

					ball = initBall(gameState.serve);
					//int t = true ? 1:3;
				}

				if(ball.pauseTime>0){
					VDP_drawText("Ready?", 17, 12);
				} else {	
					VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL3,0,FALSE,FALSE,1),17,12,6,1);
				}
				
				drawInt(player1.score,18,2,1);
				drawInt(player2.score,22,2,1);


				SPR_setHFlip (ballSprite, ball.vel.x>0);
				SPR_setPosition(ballSprite, ball.ppos.x,ball.ppos.y);
				
				SPR_setPosition(player1Sprite, player1.ppos.x,player1.ppos.y);
				SPR_setAnim(player1Sprite, player1.anim ); 
				SPR_setPosition(player2Sprite, player2.ppos.x,player2.ppos.y);
				SPR_setAnim(player2Sprite, player2.anim ); 
			}

		}
		


		SPR_update();
		VDP_waitVSync();
	}
	return (0);
}
