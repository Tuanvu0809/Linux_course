#include <stdio.h>
#include "inc/Musicplayer.h"
#include "inc/stopped.h"
#include "inc/playing.h"
#include "inc/pause.h"
#include "inc/player.h"

int main() {

    MusicPlayer *media = create_music_player((PlayerState *) new_Stop_state());
    
    if(media == NULL)
    {
        printf("Fail init media Music\n");
        return -1;
    }

    printf("Music Program..\n");
    media->clickPlayButton(media);
    media->clickStopButton(media);
    media->clickPauseButton(media);
    media->clickPlayButton(media);
    media->clickStopButton(media); 
    destroy_music_player(media);

    return 0;
}
