
#ifndef PAUSED_STATE_H
#define PAUSED_STATE_H



    #include "player.h"
    #include "Musicplayer.h"
    typedef struct{
        PlayerState base;
        MusicPlayer *content;
    } Pause_state;

    Pause_state *new_Pause_state();


#endif
