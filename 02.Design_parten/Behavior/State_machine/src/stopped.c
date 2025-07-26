// #include "../inc/player.h"
// #include "../inc/playing.h"
// #include "../inc/pause.h"
// #include "../inc/stopped.h"
// #include <stdio.h>

// static void Pause_settting(Player_state *current)
// {
//     printf("Can't pause ..\n");
// }
// static void playing_setting(Player_state *current)
// {
//     Stop_state *status = (Stop_state *)current;
//     printf("Playing..\n");
//     status->context->Change_mode(status->context, (Player_state *)new_playing_state);
// }
// static void stop_setting(Player_state *current)
// {
//     printf("Stopped already ..\n");
// }

// static void setContext(Player_state *self, Music_player *context)
// {
//     ((Pause_state *)self)->context = context;
// }

// Player_state *new_Stop_state()
// {
//     Player_state *status = (Player_state *)malloc(sizeof(Player_state));
//     status->play = playing_setting;
//     status->pause = Pause_settting;
//     status->stop = stop_setting;
//     status->set_content = NULL;
//     return (Player_state *)status;
// }


// src/stopped_state.c
#include <stdio.h>
#include <stdlib.h>
#include "../inc/stopped.h"
#include "../inc/Musicplayer.h"
#include "../inc/player.h"

typedef struct {
    PlayerState base;
    MusicPlayer *context;
} StoppedState;

static void pressPlay(PlayerState *self) {
    StoppedState *state = (StoppedState *)self;
    printf("Bắt đầu phát nhạc...\n");
    state->context->changeState(state->context, (PlayerState *)new_playing_state());
}

static void pressPause(PlayerState *self) {
    printf("Không thể tạm dừng. Nhạc chưa được phát.\n");
}

static void pressStop(PlayerState *self) {
    printf("Nhạc đã dừng sẵn rồi.\n");
}

static void setContext(PlayerState *self, MusicPlayer *context) {
    ((StoppedState *)self)->context = context;
}

PlayerState *new_stopped_state() {
    StoppedState *state = malloc(sizeof(StoppedState));
    state->base.pressPlay = pressPlay;
    state->base.pressPause = pressPause;
    state->base.pressStop = pressStop;
    state->base.setContext = setContext;
    state->context = NULL;
    return (PlayerState *)state;
}
