#include "../inc/Musicplayer.h"
#include <stdio.h>
#include <stdlib.h>

static void play_button(Music_player *Self)
{
    Self->current->play(Self->current);
}

static void stop_button(Music_player *Self)
{
    Self->current->stop(Self->current);
}

static void pause_button(Music_player *Self)
{
    Self->current->pause(Self->current);
}
static void Change_mode_function(Music_player *self, Player_state *newstate)
{
    if (self->current)
       // free(self->current);
    self->current = newstate;
    self->current->set_content(self, self->current);
}

Music_player *creat_media(Player_state *init)
{
    Music_player *player = (Music_player *)malloc(sizeof(Music_player));
    if (!player) return NULL;
  
    player->Click_play = play_button;
    player->Click_Pause = pause_button;
    player->Click_stop = stop_button;
    player->Change_mode = Change_mode_function;
    player->current = init;
    init->set_content(player, init);

    return player;
}