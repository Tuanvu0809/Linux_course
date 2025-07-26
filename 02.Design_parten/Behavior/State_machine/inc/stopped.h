#ifndef STOP_H
#define STOP_H
    #include "Musicplayer.h"
        #include <stdlib.h>

    typedef struct{
        Player_state base;
        Music_player *context;

    }Stop_state;
    Player_state *new_Stop_state();

#endif