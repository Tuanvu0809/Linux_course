// #include "../inc/player.h"
// #include "../inc/playing.h"
// #include "../inc/pause.h"
// #include "../inc/stopped.h"
// #include <stdio.h>

// static void Pause_settting(Player_state *current)
// {
//     Pause_state *status = (Pause_state *)current;
//     printf("Pause  already ..\n");
//     // status->context->Change_mode(status->context, (Player_state *)Pause_state);
// }
// static void playing_setting(Player_state *current)
// {
//     Pause_state *status = (Pause_state *)current;
//     printf("Playing..\n");
//     status->context->Change_mode(status->context, (Player_state *)new_playing_state);
// }
// static void stop_setting(Player_state *current)
// {
//     Playing_state *status = (Playing_state *)current;
//     printf("Stopped ..\n");
//     // status->context->Change_mode(status->context, (Player_state *)Stop);
// }

// static void setContext(Player_state *self, Music_player *context)
// {
//     ((Pause_state *)self)->context = context;
// }

// Player_state *new_Pause_state()
// {
//     Player_state *status = (Player_state *)malloc(sizeof(Player_state));
//     status->play = playing_setting;
//     status->pause = Pause_settting;
//     status->stop = stop_setting;
//     status->set_content =(void *) stop_setting;
//     return (Player_state *)status;
// }


// src/paused_state.c
#include <stdio.h>
#include <stdlib.h>
#include "../inc/pause.h"
#include "../inc/Musicplayer.h"
#include "../inc/playing.h"
#include "../inc/stopped.h"

typedef struct {
    PlayerState base;
    MusicPlayer *context;
} PausedState;

static void pressPlay(PlayerState *self) {
    PausedState *state = (PausedState *)self;
    printf("Tiếp tục phát nhạc...\n");
    state->context->changeState(state->context, (PlayerState *)new_playing_state());
}

static void pressPause(PlayerState *self) {
    printf("Nhạc đã được tạm dừng rồi.\n");
}

static void pressStop(PlayerState *self) {
    PausedState *state = (PausedState *)self;
    printf("Dừng nhạc khi đang tạm dừng...\n");
    state->context->changeState(state->context, (PlayerState *)new_stopped_state());
}

static void setContext(PlayerState *self, MusicPlayer *context) {
    ((PausedState *)self)->context = context;
}

PlayerState *new_paused_state() {
    PausedState *state = malloc(sizeof(PausedState));
    state->base.pressPlay = pressPlay;
    state->base.pressPause = pressPause;
    state->base.pressStop = pressStop;
    state->base.setContext = setContext;
    state->context = NULL;
    return (PlayerState *)state;
}
