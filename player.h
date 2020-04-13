#include "structs.h"

extern struct Player initPlayer(int pno);
extern struct Player updatePlayer(struct Player player, u16 input);
extern struct Player player_add_score(struct Player player);
extern struct Player player_set_winner(struct Player player);
extern struct Player player_set_loser(struct Player player);
