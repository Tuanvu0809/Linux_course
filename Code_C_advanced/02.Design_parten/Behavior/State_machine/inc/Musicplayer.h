#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

    #include "player.h"
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct MusicPlayer {
        PlayerState *currentState;
        void (*changeState)(struct MusicPlayer *self, PlayerState *newState);

        void (*clickPlayButton)();
        void (*clickPauseButton)();
        void (*clickStopButton)();
    } MusicPlayer;

    MusicPlayer *create_music_player(PlayerState *init);
    void destroy_music_player();

#endif
