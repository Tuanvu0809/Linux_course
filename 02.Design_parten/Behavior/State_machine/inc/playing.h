#ifndef PLAYING_H
#define PLAYING_H
    #include "Musicplayer.h"
        #include <stdlib.h>


    typedef struct{
        Player_state base;
        Music_player *context;

    }Playing_state;
    Player_state *new_playing_state();

#endif