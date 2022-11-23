# CSC1103-TicTacToe
CSC1103 Mini Project

List of Contents
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Installation of GTK4 for Windows](#installation-of-gtk4-for-windows)
- [Installation of GTK4 for MacOS](#installation-of-gtk4-for-macos)
- [Program Files](#program-files)
- [Program Usage for Windows](#program-usage-for-windows)
- [Program Usage for MacOS](#program-usage-for-macos)

<!-- GETTING STARTED -->
## Getting Started

This is a 3x3 Tic Tac Toe program using the C programming language, with 4 different modes [2 Player and 1 Player (Easy/ Medium/ Hard)]. To learn more about how the program works and more details on the algorithms used, please refer to the report or view the source code directly.

### Prerequisites
---
- MSYS2 (To install MINGW_64)
- GTK4 Package

### Installation of GTK4 for Windows
---
1. Install the latest version MSYS2 [from their website](https://www.msys2.org/).
2. Navigate to ```C:\msys2\``` and launch ```mingw64.exe```.
3. In the MSYS2 command prompt, enter the following
   ```sh
   pacman -S mingw-w64-x86_64-gtk4
   ```
3. Install the GTK4 packages and type 'Y' for everything.

4. To use GTK4 in Visual Studio Code, search and edit the following json files.

   a. c_cpp_properities.json 
      1) Search 'C/C++: Edit Configurations (UI)' and click on it.
      2) Replace your "includePath" with the below.
          ```sh
          "includePath": [
            "${workspaceFolder}/**",
            "C:/msys64/mingw64/include/gtk-4.0",
            "C:/msys64/mingw64/include/pango-1.0",
            "C:/msys64/mingw64/include",
            "C:/msys64/mingw64/include/glib-2.0",
            "C:/msys64/mingw64/lib/glib-2.0/include",
            "C:/msys64/mingw64/include/harfbuzz",
            "C:/msys64/mingw64/include/freetype2",
            "C:/msys64/mingw64/include/libpng16",
            "C:/msys64/mingw64/include/fribidi",
            "C:/msys64/mingw64/include/cairo",
            "C:/msys64/mingw64/include/lzo",
            "C:/msys64/mingw64/include/pixman-1",
            "C:/msys64/mingw64/include/gdk-pixbuf-2.0",
            "C:/msys64/mingw64/include/graphene-1.0",
            "C:/msys64/mingw64/lib/graphene-1.0/include"
          ], 
          ```
   b. task.json
      1) Replace your "args" with the following 
          ```sh
          "args": [
              "-fdiagnostics-color=always",
              "-g",
              "${file}",
              "-o",
              "${fileDirname}\\${fileBasenameNoExtension}.exe",
              "-IC:/msys64/mingw64/include/gtk-4.0",
              "-IC:/msys64/mingw64/include/pango-1.0",
              "-IC:/msys64/mingw64/include",
              "-IC:/msys64/mingw64/include/glib-2.0",
              "-IC:/msys64/mingw64/lib/glib-2.0/include",
              "-IC:/msys64/mingw64/include/harfbuzz",
              "-IC:/msys64/mingw64/include/freetype2",
              "-IC:/msys64/mingw64/include/libpng16",
              "-IC:/msys64/mingw64/include/fribidi",
              "-IC:/msys64/mingw64/include/cairo",
              "-IC:/msys64/mingw64/include/lzo",
              "-IC:/msys64/mingw64/include/pixman-1",
              "-IC:/msys64/mingw64/include/gdk-pixbuf-2.0",
              "-IC:/msys64/mingw64/include/graphene-1.0",
              "-IC:/msys64/mingw64/lib/graphene-1.0/include",
              "-mfpmath=sse",
              "-msse",
              "-msse2",
              "-LC:/msys64/mingw64/lib",
              "-lgtk-4",
              "-lpangowin32-1.0",
              "-lpangocairo-1.0",
              "-lpango-1.0",
              "-lharfbuzz",
              "-lgdk_pixbuf-2.0",
              "-lcairo-gobject",
              "-lcairo",
              "-lgraphene-1.0",
              "-lgio-2.0",
              "-lgobject-2.0",
              "-lglib-2.0",
              "-lintl"
          ],
          ```

### Installation of GTK4 for MacOS
---
1. Install GTK4 using Homebrew by running the following command
   ```sh
   brew install gtk4
   ```

### Program Files
---
```
README.md (this file)

game/ (contains main program, source and header files)

train-ml/ (multi-linear regression model training files)
```

In ```game/```, we have the following files:
```
files/header/config.h (configuration file)

files/header/miniaudio.h (miniaudio header file)

files/routes/gameController.c (contains game functions)

files/routes/gtkGUI.c (contains GTK GUI functions)

files/routes/board.c (contains creation of Tic Tac Toe board)

files/routes/setting.c (contains functions of the setting bar - Start, Quit, Restart, Mode Dropdown)

files/routes/scoreboard.c (contains scoreboard functions)

files/routes/twoplayer.c (contains two player mode function)

files/routes/minimax.c (contains minimax algorithm)

files/routes/machineLearn.c (contains machine learning model functions)

files/routes/misc.c (contains miscellaneous functions to call audio and css files)

files//sound (contains audio files for game)

files/styles.css (contains css for GUI)

files/weights.txt (contains optimal model weights)

game.c (main program)

run_win.bat (script for running program - Windows)

run_win.sh (script for running program - Mac)
```

### Program Usage for Windows
---
1. Download source code 
2. Compile the program in command prompt.<br>
   ```
   gcc -o tictactoe game.c files/routes/*.c -mwindows -IC:/msys64/mingw64/include/gtk-4.0 -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include/freetype2 -IC:/msys64/mingw64/include/libpng16 -IC:/msys64/mingw64/include/fribidi -IC:/msys64/mingw64/include/cairo -IC:/msys64/mingw64/include/lzo -IC:/msys64/mingw64/include/pixman-1 -IC:/msys64/mingw64/include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/include/graphene-1.0 -IC:/msys64/mingw64/lib/graphene-1.0/include -IC:/msys64/mingw64/include/pango-1.0 -LC:/msys64/mingw64/lib -lgtk-4 -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lgraphene-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl
   ```
3. Run the program!<br>
   ```sh
   tictactoe.exe
   ```

Alternatively, you can directly run ```run_win.bat``` in Command Prompt to compile and run the executable created.
  
### Program Usage for MacOS
---
1. Download source code 
2. Compile the program.<br>
   ```sh
   gcc `pkg-config --cflags --libs gtk4` -o tictactoe game.c ./files/routes/*.c`
   ```
3. Run the program!<br>
   ```sh 
   ./tictactoe
   ```
  
Alternatively, the ```run_mac.sh``` script can be executed on a terminal to compile and run the program directly.
