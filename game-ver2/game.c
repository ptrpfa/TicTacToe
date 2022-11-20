#include <stdlib.h>                 // Include standard library
#include <gtk/gtk.h>                // Include GTK library for GUI
#include "files/header/config.h"       // Include configuration file

//Global Variable Init
int gameModeOption = -1; 
int player = -1;

// Program entrypoint
int main (int argc, char**argv) {
    // Read in ML model's weights
    readWeights();

    //** GTKApplication Object **//
    GtkApplication* app; // app is the GTKApplication 
    int status;
    app = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS);   // Init App, Parameter: application name, flags for special needs 
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);  // Connect App with the 'activate' function, or the settings for the GUI
    status = g_application_run(G_APPLICATION(app), argc, argv);     // Accepts command line argument with argc and argv
    g_object_unref(app);                                            // Remove it from memory
    //** GTKAppliation Object **//

    //Remove the miniaudio engine
    miniaudio_close();
    
    // End of program
    return status;
}



