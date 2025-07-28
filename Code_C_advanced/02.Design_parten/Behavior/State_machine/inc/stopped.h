#ifndef STOPPED_STATE_H
#define STOPPED_STATE_H
    #include "player.h"
    #include "Musicplayer.h"
    typedef struct{
        PlayerState base;
        MusicPlayer *content;
    } Stop_state;

    Stop_state *new_Stop_state();

#endif
