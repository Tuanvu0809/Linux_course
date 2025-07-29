#include <stdio.h>
#include "inc/Musicplayer.h"
#include "inc/stopped.h"
#include "inc/playing.h"
#include "inc/pause.h"
#include "inc/player.h"

int main() {

    MusicPlayer const *media = create_music_player((PlayerState *) new_Stop_state());
    
    if(media == NULL)
    {
        printf("Fail init media Music\n");
        return -1;
    }

    printf("Music Program..\n");
    media->clickPlayButton();
    media->clickStopButton();
    media->clickPauseButton();
    media->clickPlayButton();
    media->clickPauseButton();
    media->clickPlayButton();
    media->clickStopButton(); 
    destroy_music_player();

    return 0;
}
