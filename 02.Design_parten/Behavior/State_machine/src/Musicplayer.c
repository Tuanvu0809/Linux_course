#include "../inc/Musicplayer.h"
#include <stdio.h>

static void Click_play(MusicPlayer *current)
{
    printf("Click play button : ");
    current->currentState->pressPlay(current->currentState);
}

static void Click_stop(MusicPlayer *current)
{
    printf("Click stop button : ");
    current->currentState->pressStop(current->currentState);
}

static void Click_pause(MusicPlayer *current)
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
    MusicPlayer *creat_music = (MusicPlayer*) malloc(sizeof(MusicPlayer));
  // if(creat_music == NULL ) return NULL;

    creat_music->clickStopButton = Click_stop;
    creat_music->clickPlayButton = Click_play;
    creat_music->clickPauseButton = Click_pause;
    creat_music->changeState = change_content;
    creat_music->currentState = init;
    init->setContext(init,creat_music);

    return creat_music;
}

void destroy_music_player(MusicPlayer *self)
{
    if(self == NULL ){
        printf("Can't free.\n");
        return ;
    }

    free(self);
    printf("memory has been delete\n ");
}

