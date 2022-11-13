#!/usr/bin/env bash
gcc `pkg-config allegro_main-5 allegro_acodec-5 gtk4 --libs --cflags` -o tictactoe game.c
./tictactoe