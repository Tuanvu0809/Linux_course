#ifndef PLAYING_H
#define PLAYING_H
    #include "Musicplayer.h"

    typedef struct{
        Player_state base;
        Music_player *context;

    }Playing_state;
    Player_state (*playing)();

#endif