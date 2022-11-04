# CSC1103-TicTacToe
CSC1103 Mini Project

<!-- GETTING STARTED -->
## Getting Started

Meow Meow Meow, for the GUI version do download the TicTacToe.c file

### Prerequisites

-GTK4 requried
-MSYS2 required (the one used to install your MINGW_64)

### Installation

_Below is the instruction for installing GTk4._

1. Search for 'MSYS2 MSYS' in your computer.
2. Run the application.
3. In the MSYS2 command prompt, enter the following
   ```sh
   pacman -S mingw-w64-x86_64-gtk4
   ```
3. Install the GTK4 packages and type 'Y' for everything.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage

_Search and edit your 'c_cpp_properities.json file' to add GTK libs

1. In Visual Studios, use following command for Window Laptop.
   ```sh
   Ctrl+Shift+P
   ```
2. Search 'C/C++: Edit Configurations (UI)' and click on it.
3. Replace your "includePath" with the below.
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
_Edit your 'task.json' folder to include GTK4 Libs_
1. Open your '.vscode' folder in Visual Studio, under your explorer tab.
2. CLick on 'task.json'
3. Replace your "args" with the following 
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
    
_Now you should run without error_


_Allegro 5 Library Download:_

1) Open Msys2 (The purple icon one) and type in the following command :
   ```sh
  pacman -S mingw-w64-x86_64-allegro
   ```
2) Head over to task.json and add the following libs into your args
   ```sh
    "args": [
            "-lintl",
            "-lallegro_audio",
            "-lallegro",
            "-lallegro_acodec"
    ],
    ```
3) Include the "sound" folder where all the sound effects are stored in
4) You can run the program now
               
<p align="right">(<a href="#readme-top">back to top</a>)</p>
