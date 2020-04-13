
#define LEFT_EDGE  0
#define SCREEN_WIDTH  320
#define TOP_EDGE  0
#define SCREEN_HEIGHT  224
#define SCREEN_MIDDLE  112

#define BALL_XO  4
#define BALL_YO  4
#define BALL_HEIGHT  8

#define PLAYER_YO  16
#define PLAYER_HEIGHT  32

#define SWING_COOLDOWN  0
#define SWING_TIME  10


#define SCORE_LIMIT  5

/*
Notes regarding SGDK API changes:

  type
  - Map --> TileMap
  - VDPPlan --> VDPPlane
  var / const
  - PLAN_A --> BG_A
  - PLAN_B --> BG_B
  - PLAN_WINDOW --> WINDOW
  - VDP_PLAN_A --> VDP_BG_A
  - VDP_PLAN_B --> VDP_BG_B
  - VDP_PLAN_WINDOW --> VDP_WINDOW
 
 From https://github.com/Stephane-D/SGDK/commit/c1ce6edbefa4eddc709aec24af0aec9fbe5df84f
  */
