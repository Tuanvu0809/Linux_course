// #include "../inc/player.h"
// #include "../inc/playing.h"
// #include "../inc/pause.h"
// #include "../inc/stopped.h"
// #include <stdio.h>

// static void Pause_settting(Player_state *current)
// {
//     Playing_state *status = (Playing_state *)current;
//     printf("Pause ..\n");
//     status->context->Change_mode(status->context, (Player_state *)new_Pause_state);
// }
// static void playing_setting(Player_state *current)
// {
//     printf("Playing already..\n");
// }
// static void stop_setting(Player_state *current)
// {
//     Playing_state *status = (Playing_state *)current;
//     printf("Stopped ..\n");
//     status->context->Change_mode(status->context, (Player_state *)new_Stop_state);
// }

// static void setContext(Player_state *self, Music_player *context)
// {
//     ((Playing_state *)self)->context = context;
// }

// Player_state *new_playing_state()
// {
//     Player_state *status = (Player_state *)malloc(sizeof(Player_state));
//     status->play = playing_setting;
//     status->pause = Pause_settting;
//     status->stop = stop_setting;
//     status->set_content = NULL;
//     return (Player_state *)status;
// }


// src/playing_state.c
#include <stdio.h>
#include <stdlib.h>
#include "../inc/playing.h"
#include "../inc/Musicplayer.h"
#include "../inc/stopped.h"
#include "../inc/pause.h"

typedef struct {
    PlayerState base;
    MusicPlayer *context;
} PlayingState;

static void pressPlay(PlayerState *self) {
    printf("Nhạc đang phát rồi. Không thể phát lại.\n");
}

static void pressPause(PlayerState *self) {
    PlayingState *state = (PlayingState *)self;
    printf("Tạm dừng nhạc...\n");
    state->context->changeState(state->context, (PlayerState *)new_paused_state());
}

static void pressStop(PlayerState *self) {
    PlayingState *state = (PlayingState *)self;
    printf("Dừng phát nhạc...\n");
    state->context->changeState(state->context, (PlayerState *)new_stopped_state());
}

static void setContext(PlayerState *self, MusicPlayer *context) {
    ((PlayingState *)self)->context = context;
}

PlayerState *new_playing_state() {
    PlayingState *state = malloc(sizeof(PlayingState));
    state->base.pressPlay = pressPlay;
    state->base.pressPause = pressPause;
    state->base.pressStop = pressStop;
    state->base.setContext = setContext;
    state->context = NULL;
    return (PlayerState *)state;
}
