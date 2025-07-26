// #ifndef STOP_H
// #define STOP_H
//     #include "Musicplayer.h"
//         #include <stdlib.h>

//     typedef struct{
//         Player_state base;
//         Music_player *context;

//     }Stop_state;
//     Player_state *new_Stop_state();

// #endif

// inc/stopped_state.h
#ifndef STOPPED_STATE_H
#define STOPPED_STATE_H

#include "player.h"

PlayerState *new_stopped_state();

#endif
