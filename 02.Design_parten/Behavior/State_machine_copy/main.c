// #include <stdio.h>
// #include "inc/Musicplayer.h"
// #include "inc/pause.h"
// #include "inc/playing.h"
// #include "inc/stopped.h"

// int main()
// {

//     printf("Media music player: \n");
   



//     return 0;
// }

// main.c
#include <stdio.h>
#include "inc/Musicplayer.h"
#include "inc/stopped.h"

int main() {
    MusicPlayer *player = create_music_player(new_stopped_state());

    printf("=== Mô phỏng người dùng ===\n");

    // player->clickPlayButton();   // Stopped -> Playing
    // player->clickPauseButton();  // Playing -> Paused
    // player->clickPlayButton();   // Paused -> Playing
    // player->clickStopButton();   // Playing -> Stopped
    // player->clickPauseButton();  // Stopped -> không làm gì

    destroy_music_player(player);
    return 0;
}
