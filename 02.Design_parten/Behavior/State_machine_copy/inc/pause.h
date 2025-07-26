// #ifndef PAUSE_H
// #define PAUSE_H
//     #include "Musicplayer.h"
//     #include <stdlib.h>

//     typedef struct{
//         Player_state base;
//         Music_player *context;
//     }Pause_state;

//     Player_state *new_Pause_state();

// #endif

// inc/paused_state.h
#ifndef PAUSED_STATE_H
#define PAUSED_STATE_H

#include "player.h"

PlayerState *new_paused_state();

#endif
