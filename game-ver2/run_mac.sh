#!/usr/bin/env bash
gcc `pkg-config --cflags --libs gtk4` -o tictactoe game.c ./files/routes/*.c
./tictactoe