#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

    #include "player.h"
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct MusicPlayer {
        PlayerState *currentState;
        void (*changeState)(struct MusicPlayer *self, PlayerState *newState);

        void (*clickPlayButton)(struct MusicPlayer *self);
        void (*clickPauseButton)(struct MusicPlayer *self);
        void (*clickStopButton)(struct MusicPlayer *self);
    } MusicPlayer;

    MusicPlayer *create_music_player(PlayerState *init);
    void destroy_music_player(MusicPlayer *self);

#endif
