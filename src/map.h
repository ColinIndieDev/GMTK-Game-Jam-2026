#pragma once

#include <cpl/cpl.h>

#define TILE_SIZE 50

enum {
    LEVEL_0 = 0,
    TOTAL_LEVELS,
};

void init_levels();
tilemap *get_level_tilemap(int level);
void draw_level(int level);
