// #ifndef PLAYER_H
// #define PLAYER_H

//     struct Music_player;

//     typedef struct Player_state
//     {

//         void (*stop)(struct Player_state *current);
//         void (*play)(struct Player_state *current);
//         void (*pause)(struct Player_state *current);
//         void (*set_content)(struct Music_player *self,struct Player_state *current);

//     } Player_state;

// #endif
// inc/player_state.h
#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

struct MusicPlayer;

typedef struct PlayerState {
    void (*pressPlay)(struct PlayerState *self);
    void (*pressPause)(struct PlayerState *self);
    void (*pressStop)(struct PlayerState *self);
    void (*setContext)(struct PlayerState *self, struct MusicPlayer *player);
} PlayerState;

#endif
