#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

    #include "Player.h"

    typedef struct Music_player {
        Player_state *current;

        void (*Click_play)(struct Music_player *self);
        void (*Click_Pause)(struct Music_player *self);
        void (*Click_stop)(struct Music_player *self);
        void (*Change_mode)(struct Music_player *self, Player_state *newState);
    } Music_player;

    Music_player *creat_media(Player_state *init);

#endif