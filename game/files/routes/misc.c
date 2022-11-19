#include <gtk/gtk.h>                // Include GTK library for GUI
#include <time.h>                   // Include time functions
#include "../header/config.h"       // Include configuration file
#include "../header/miniaudio.h"    // Include miniaudio file

/* Miscellaneous Functions */
//MiniAudio Variables
ma_engine miniaudio_engine;

// Function to delay for a specified amount of seconds
void delay(float seconds){
    // Calculate number of clock cycles to wait for
    clock_t wait = CLOCKS_PER_SEC * seconds;
    // Get total number of clock cycles at the start
    clock_t start = clock();
    // Wait until the stipulated time has passed
    while(clock() < start + wait);
}

// Function to set the CSS styling for the GUI
void CreateCSS(GtkWidget *widget, const char *class_name){
    GtkCssProvider *provider2;
    GtkStyleContext *context2;

    //Init CSS
    context2 = gtk_widget_get_style_context(widget);
    provider2 = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider2, STYLES_FILE);
    gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);

    //Create Class
    if(class_name != NULL){
        gtk_style_context_add_class(context2, class_name);
    }
}

//Function to init the MiniAudio Lib
void miniaudio_init(){
    // Initialise Mini Audio engine
    ma_result miniaudio_result;
    miniaudio_result = ma_engine_init(NULL, &miniaudio_engine);
    // Check if the MA engine has been initialised successfully
    if (miniaudio_result != MA_SUCCESS) {
        printf("Failed to initialize Mini Audio Engine!");
        exit(1);
    }
}

void miniaudio_close(){
    // Close Mini Audio engine
    ma_engine_uninit(&miniaudio_engine);
}

// Function to play an audio sound effect
void audio(const char *audio_file){
    // Play audio  file
    ma_engine_play_sound(&miniaudio_engine, audio_file, NULL);
}
