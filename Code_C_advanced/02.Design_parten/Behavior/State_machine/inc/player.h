#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

    struct MusicPlayer;

    typedef struct PlayerState {
        void (*pressPlay)(struct PlayerState *self);
        void (*pressPause)(struct PlayerState *self);
        void (*pressStop)(struct PlayerState *self);
        void (*setContext)(struct PlayerState *self, struct MusicPlayer *player);
    
    } PlayerState;

#endif
