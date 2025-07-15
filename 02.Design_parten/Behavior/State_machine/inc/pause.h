#ifndef PAUSE_H
#define PAUSE_H
    #include "Musicplayer.h"

    typedef struct{
        Player_state base;
        Music_player *context;
    }Pause_state;

    Player_state (*Pause)();

#endif