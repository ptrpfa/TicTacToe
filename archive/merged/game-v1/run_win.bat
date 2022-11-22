@ECHO OFF
@REM GCC compile the files
gcc -o tictactoe game.c files/routes/*.c -mwindows -IC:/msys64/mingw64/include/gtk-4.0 -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include/freetype2 -IC:/msys64/mingw64/include/libpng16 -IC:/msys64/mingw64/include/fribidi -IC:/msys64/mingw64/include/cairo -IC:/msys64/mingw64/include/lzo -IC:/msys64/mingw64/include/pixman-1 -IC:/msys64/mingw64/include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/include/graphene-1.0 -IC:/msys64/mingw64/lib/graphene-1.0/include -IC:/msys64/mingw64/include/pango-1.0 -LC:/msys64/mingw64/lib -lgtk-4 -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lgraphene-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl

@REM RUN the executable
tictactoe