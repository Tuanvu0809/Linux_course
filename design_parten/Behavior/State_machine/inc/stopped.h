#ifndef STOP_H
#define STOP_H
    #include "Musicplayer.h"

    typedef struct{
        Player_state base;
        Music_player *context;

    }Stop_state;
    Player_state (*Stop)();

#endif