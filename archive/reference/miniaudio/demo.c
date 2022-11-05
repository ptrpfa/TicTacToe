#include <gtk/gtk.h>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

// Initialise miniaudio variables
ma_result miniaudio_result;
ma_engine miniaudio_engine;

void playAudio(char * audio_file, ma_engine * ptr_engine) {
    ma_engine_play_sound(ptr_engine, audio_file, NULL);
    return;
}

static void activate (GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    gtk_widget_show (window);
}

int main (int argc, char **argv) {

    // Initialise miniaudio engine
    miniaudio_result = ma_engine_init(NULL, &miniaudio_engine);
    // Check if the engine has been initialised successfully
    if (miniaudio_result != MA_SUCCESS) {
        printf("Failed to initialize audio miniaudio_engine.");
        return -1;
    }

     // Play sound
    playAudio("sound/biu.wav", &miniaudio_engine);

    GtkApplication *app;
    int status;
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    

    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}