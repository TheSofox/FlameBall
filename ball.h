
#include "structs.h"
#include <genesis.h>

extern bool check_ball_hit(struct Ball ball, struct Player player);
extern struct Ball initBall(int serve);
extern struct Vector2f hitBall(struct Ball ball, struct Player player);
extern struct Ball updateBall(struct Ball ball, struct Player player1, struct Player player2);
