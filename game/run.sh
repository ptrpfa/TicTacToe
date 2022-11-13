#!/usr/bin/env bash
gcc `pkg-config --cflags --libs gtk4` -o tictactoe game.c
./tictactoe