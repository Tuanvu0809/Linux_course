// #ifndef MUSIC_PLAYER_H
// #define MUSIC_PLAYER_H

//     #include "Player.h"

//     typedef struct Music_player {
//         Player_state *current;

//         void (*Click_play)(struct Music_player *self);
//         void (*Click_Pause)(struct Music_player *self);
//         void (*Click_stop)(struct Music_player *self);
//         void (*Change_mode)(struct Music_player *self, Player_state *newState);
//     } Music_player;

//     Music_player *creat_media(Player_state *init);

// #endif

// inc/music_player.

#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

    #include "player.h"

    typedef struct MusicPlayer {
        PlayerState *currentState;
        void (*changeState)(struct MusicPlayer *self, PlayerState *newState);

        void (*clickPlayButton)(struct MusicPlayer *self);
        void (*clickPauseButton)(struct MusicPlayer *self);
        void (*clickStopButton)(struct MusicPlayer *self);
    } MusicPlayer;

    MusicPlayer *create_music_player(PlayerState *initialState);
    void destroy_music_player(MusicPlayer *player);

#endif
