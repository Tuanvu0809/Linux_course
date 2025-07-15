#ifndef PLAYER_H
#define PLAYER_H

typedef struct Music_player;
// typedef struct Player_state;

typedef struct Player_state
{

    void (*stop)(Player_state *current);
    void (*play)(Player_state *current);
    void (*pause)(Player_state *current);
    void (*set_content)(struct Music_player *self, Player_state *current);

} Player_state;

#endif