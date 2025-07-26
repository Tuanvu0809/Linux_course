// #include "../inc/Musicplayer.h"
// #include <stdio.h>
// #include <stdlib.h>

// static void play_button(Music_player *Self)
// {
//     Self->current->play(Self->current);
// }

// static void stop_button(Music_player *Self)
// {
//     Self->current->stop(Self->current);
// }

// static void pause_button(Music_player *Self)
// {
//     Self->current->pause(Self->current);
// }
// static void Change_mode_function(Music_player *self, Player_state *newstate)
// {
//     if (self->current)
//         free(self->current);
//     self->current = newstate;
//     self->current->set_content(self, self->current);
// }

// Music_player *creat_media(Player_state *init)
// {
//     Music_player *player = (Music_player *)malloc(sizeof(Music_player));

  
//     player->Click_play = play_button;
//     player->Click_Pause = pause_button;
//     player->Click_stop = stop_button;
//     player->Change_mode = Change_mode_function;
//     player->current = init;
//     init->set_content(player, init);

//     return player;
// }

// src/music_player.c
#include <stdlib.h>
#include <stdio.h>
#include "../inc/Musicplayer.h"

static void changeState(MusicPlayer *self, PlayerState *newState) {
    if (self->currentState)
        free(self->currentState);
    self->currentState = newState;
    self->currentState->setContext(self->currentState, self);
}

static void clickPlayButton(MusicPlayer *self) {
    self->currentState->pressPlay(self->currentState);
}

static void clickPauseButton(MusicPlayer *self) {
    self->currentState->pressPause(self->currentState);
}

static void clickStopButton(MusicPlayer *self) {
    self->currentState->pressStop(self->currentState);
}

MusicPlayer *create_music_player(PlayerState *initialState) {
    MusicPlayer *player = malloc(sizeof(MusicPlayer));
    player->changeState = changeState;
    player->clickPlayButton = clickPlayButton;
    player->clickPauseButton = clickPauseButton;
    player->clickStopButton = clickStopButton;
    player->currentState = initialState;
    initialState->setContext(initialState, player);
    return player;
}

void destroy_music_player(MusicPlayer *player) {
    if (player->currentState)
        free(player->currentState);
    free(player);
}
