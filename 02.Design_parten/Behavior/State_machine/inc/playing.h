#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

    #include "player.h"
    #include "Musicplayer.h"
    typedef struct{
        PlayerState base;
        MusicPlayer *content;
    } Playing_state;

    Playing_state *new_playing_state();

#endif
