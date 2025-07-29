#include "../inc/Musicplayer.h"
#include <stdio.h>

static MusicPlayer *current;

static void Click_play()
{
    printf("Click play button : ");
    current->currentState->pressPlay(current->currentState);
}

static void Click_stop()
{
    printf("Click stop button : ");
    current->currentState->pressStop(current->currentState);
}

static void Click_pause()
{
    printf("Click Pause button : ");
    current->currentState->pressPause(current->currentState);
}

static void change_content(MusicPlayer *current,PlayerState *newstate )
{
    if(current->currentState)
        free(current->currentState);
    current->currentState = newstate;
    current->currentState->setContext(current->currentState,current);
}

MusicPlayer *create_music_player(PlayerState *init)
{   
    current = (MusicPlayer*) malloc(sizeof(MusicPlayer));

    current->clickStopButton = Click_stop;
    current->clickPlayButton = Click_play;
    current->clickPauseButton = Click_pause;
    current->changeState = change_content;
    current->currentState = init;
    init->setContext(init,current);

    return current;
}

void destroy_music_player()
{
    if(current == NULL ){
        printf("Can't free.\n");
        return ;
    }

    free(current);
    printf("memory has been delete\n ");
}

