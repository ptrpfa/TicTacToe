#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <stdio.h>
#include <gtk/gtk.h>

// Global variables

// Initialise miniaudio variables
ma_result miniaudio_result;
ma_engine miniaudio_engine;


void playAudio(char * audio_file, ma_engine * ptr_engine) {
    ma_engine_play_sound(ptr_engine, audio_file, NULL);
    return;
}

int main(int argc, char** argv)
{   

    // Initialise miniaudio engine
    miniaudio_result = ma_engine_init(NULL, &miniaudio_engine);
    // Check if the engine has been initialised successfully
    if (miniaudio_result != MA_SUCCESS) {
        printf("Failed to initialize audio miniaudio_engine.");
        return -1;
    }

    // Play sound
    playAudio("sound/biu.wav", &miniaudio_engine);
    playAudio("sound/beepboop.wav", &miniaudio_engine);
    // ma_engine_play_sound(&miniaudio_engine, "biu.wav", NULL);
    // ma_engine_play_sound(&miniaudio_engine, "beepboop.wav", NULL);


    printf("Press Enter to quit...");
    getchar();
    int i = 1;
    
    // Uniniitialise miniaudio engine
    ma_engine_uninit(&miniaudio_engine);

    return 0;
}