#include "ball.h"
#include "constants.h"

bool check_ball_hit(struct Ball ball, struct Player player){
	return  (ball.pos.x + BALL_XO>= player.pos.x) && (ball.pos.x + BALL_XO<= player.pos.x + PLAYER_HEIGHT) && 
			(ball.pos.y + BALL_YO>= player.pos.y) && (ball.pos.y + BALL_YO<= player.pos.y + PLAYER_HEIGHT)
			&& player.hitFrame;
}


struct Ball initBall(int serve){
	struct Ball ball;
	ball.pos.x = SCREEN_WIDTH/2;
	ball.pos.y = SCREEN_MIDDLE;
	ball.vel.x = 1*serve;
	ball.vel.y = 0;
	ball.offside = 0;
	ball.pauseTime = 120;
	ball.justHit = FALSE;
	return ball;
}
struct Vector2f hitBall(struct Ball ball, struct Player player){
	ball.vel.x *= -1.05;
	ball.vel.y += player.vel.y/2;
	
	ball.vel.y += ((ball.pos.y + 4.0f) - (player.pos.y + 16.0f))/20;
	return ball.vel;
}

struct Ball updateBall(struct Ball ball, struct Player player1, struct Player player2){
	if(ball.pauseTime>0){
		ball.pauseTime-=1;
		ball.ppos.x = ball.pos.x;
		ball.ppos.y = ball.pos.y;
		return ball;
	}
	ball.justHit = FALSE;
	if (ball.vel.x<0 && check_ball_hit(ball, player1)){
		ball.vel = hitBall(ball, player1);
		ball.justHit = TRUE;
	}
	if (ball.vel.x>0 && check_ball_hit(ball, player2)){
		ball.vel = hitBall(ball, player2);
		ball.justHit = TRUE;
	}
	if (ball.pos.y <= 0){
		ball.vel.y *= -1;
	}
	if (ball.pos.y + BALL_HEIGHT > SCREEN_HEIGHT){
		ball.vel.y *= -1;
	}
	if(ball.pos.x <= 0){
		ball.offside = -1;
	}
	if(ball.pos.x>=SCREEN_WIDTH){
		ball.offside = 1;
	}
	
	ball.pos.x = ball.pos.x + ball.vel.x;
	ball.pos.y = ball.pos.y + ball.vel.y;
	
	ball.ppos.x = ball.pos.x;
	ball.ppos.y = ball.pos.y;
	
	return ball;
};
