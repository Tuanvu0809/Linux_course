#include "../inc/player.h"
#include "../inc/playing.h"
#include "../inc/pause.h"
#include "../inc/stopped.h"
#include <stdio.h>

static void Pause_settting(Player_state *current)
{
    Pause_state *status = (Pause_state *)current;
    printf("Pause  already ..\n");
    // status->context->Change_mode(status->context, (Player_state *)Pause_state);
}
static void playing_setting(Player_state *current)
{
    Pause_state *status = (Pause_state *)current;
    printf("Playing..\n");
    status->context->Change_mode(status->context, (Player_state *)new_playing_state);
}
static void stop_setting(Player_state *current)
{
    Playing_state *status = (Playing_state *)current;
    printf("Stopped ..\n");
    // status->context->Change_mode(status->context, (Player_state *)Stop);
}

static void setContext(Player_state *self, Music_player *context)
{
    ((Pause_state *)self)->context = context;
}

Player_state *new_Pause_state()
{
    Player_state *status = (Player_state *)malloc(sizeof(Player_state));
    status->play = playing_setting;
    status->pause = Pause_settting;
    status->stop = stop_setting;
    status->set_content =(void *) stop_setting;
    return (Player_state *)status;
}