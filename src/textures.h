#pragma once

#include <cpl/cpl.h>

enum {
    TEXTURE_RIFLE = 0,
    TEXTURE_BULLET,
    TEXTURE_PLAYER_IDLE0,
    TEXTURE_PLAYER_IDLE1,
    TEXTURE_PLAYER_GUN_IDLE0,
    TEXTURE_PLAYER_GUN_IDLE1,
    TOTAL_TEXTURES
};

void init_textures();
texture *get_texture(int id);
