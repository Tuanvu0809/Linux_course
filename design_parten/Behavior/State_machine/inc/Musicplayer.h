#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "Player.h"

typedef struct Music_player
{
    Player_state *current;
    void (*Change_mode)(struct Music_player *self, Player_state *current);

    void (*Click_play)(Player_state *current);
    void (*Click_Pause)(Player_state *current);
    void (*Click_stop)(Player_state *current);
} Music_player;

#endif