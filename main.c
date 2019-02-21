#include <stdio.h>

// JSON object
{
    "seed": 1234,
    "width": 14,
    "height": 14,
    "entry": 1,
    "exit": 196,
    "cells": [[{"north": true, "south": true, "east": false, "west": false}, ...], ...]
}
 
// C data structures
 
struct cell {
    boolean north;
    boolean south;
    boolean east;
    boolean west;
}
 
struct labyrinth {
    int seed;
    int width;
    int height;
    int entry;
    int exit;
    struct cell **cells;
}

int main()
{
	printf("Hello, world");
	return 0;
}


