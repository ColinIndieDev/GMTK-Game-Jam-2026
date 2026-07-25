#pragma once

#include <cpl/cpl.h>
#include "player.h"

#define TILE_SIZE 50

#define LEVEL_COUNT 2

void init_levels();
tilemap *get_level_tilemap(int level);
void draw_level(int level);
void update_level(int *level);
