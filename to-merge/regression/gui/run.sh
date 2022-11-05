#!/usr/bin/env bash
gcc `pkg-config --cflags --libs gtk4` -o TicTacToe tictactoe.c
./TicTacToe