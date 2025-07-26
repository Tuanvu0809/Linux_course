#ifndef PLAYER_H
#define PLAYER_H

    struct Music_player;

    typedef struct Player_state
    {

        void (*stop)(struct Player_state *current);
        void (*play)(struct Player_state *current);
        void (*pause)(struct Player_state *current);
        void (*set_content)(struct Music_player *self,struct Player_state *current);

    } Player_state;

#endif