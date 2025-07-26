#include "../inc/playing.h"
#include "../inc/stopped.h"
#include "../inc/pause.h"
static void press_play_button(PlayerState *self)
{
    Stop_state *state = (Stop_state *) self;
    printf("[stopped]--> playing Music...\n");
    state->content->changeState(state->content,(PlayerState *) new_playing_state());

}

static void press_stop_button(PlayerState *self)
{
    printf("[stopped]--> already stop Music..\n");
}

static void press_pause_button(PlayerState *self)
{
    printf("[stopped]--> Can't pause\n");
}   
static void set_change(PlayerState *self, MusicPlayer *player)
{
    ((Stop_state *)self)->content = player; 
}

Stop_state  *new_Stop_state(){
    Stop_state *new = (Stop_state *) malloc(sizeof(Stop_state));

    new->base.pressPlay = press_play_button;
    new->base.pressStop = press_stop_button;
    new->base.pressPause = press_pause_button;
    new->base.setContext = set_change;

    return new;
}