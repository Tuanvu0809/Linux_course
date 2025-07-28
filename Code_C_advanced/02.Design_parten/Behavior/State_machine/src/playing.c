#include "../inc/playing.h"
#include "../inc/stopped.h"
#include "../inc/pause.h"
static void press_play_button(PlayerState *self)
{
    printf("[Playing Mode]--> already playing Music...\n");

}

static void press_stop_button(PlayerState *self)
{
    Playing_state *state = (Playing_state *) self;
    printf("[Playing Mode]--> stop Music..\n");
    state->content->changeState(state->content,(PlayerState *) new_Stop_state());
}

static void press_pause_button(PlayerState *self)
{
    Playing_state *state = (Playing_state *) self;
    printf("[Playing Mode]--> Pause Music ..\n");
    state->content->changeState(state->content,(PlayerState *) new_Pause_state());
}
static void set_change(PlayerState *self, MusicPlayer *player)
{
    ((Playing_state *)self)->content = player; 
}

Playing_state  *new_playing_state(){
    Playing_state *new = (Playing_state *) malloc(sizeof(Playing_state));

    new->base.pressPlay = press_play_button;
    new->base.pressStop = press_stop_button;
    new->base.pressPause = press_pause_button;
    new->base.setContext = set_change;

    return new;
}