#include "../inc/playing.h"
#include "../inc/stopped.h"
#include "../inc/pause.h"
static void press_play_button(PlayerState *self)
{
    Pause_state *state = (Pause_state *) self;
    printf("[pause]-->playing Music...\n");
    state->content->changeState(state->content,(PlayerState *) new_playing_state());

}

static void press_stop_button(PlayerState *self)
{
   printf("[pause]--> Can't stop Music..\n");
    
}

static void press_pause_button(PlayerState *self)
{
    printf("[pause]-->Pause Music ..\n");
}
static void set_change(PlayerState *self, MusicPlayer *player)
{
    ((Pause_state *)self)->content = player; 
}

Pause_state  *new_Pause_state(){
    Pause_state *new = (Pause_state *) malloc(sizeof(Pause_state));

    new->base.pressPlay = press_play_button;
    new->base.pressStop = press_stop_button;
    new->base.pressPause = press_pause_button;
    new->base.setContext = set_change;

    return new;
}