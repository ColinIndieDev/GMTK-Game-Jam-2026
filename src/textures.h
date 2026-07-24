#pragma once

#include <cpl/cpl.h>

#define MAX_FRAMES_SPRITE_SHEET 8

enum {
    SPRITE_SHEET_RIFLE = 0,
    SPRITE_SHEET_BULLET,
    SPRITE_SHEET_PLAYER_IDLE,
    SPRITE_SHEET_PLAYER_GUN_IDLE,
    SPRITE_SHEET_PLAYER_WALK,
    TOTAL_SPRITE_SHEETS,
};

typedef struct {
    int count;
    texture textures[MAX_FRAMES_SPRITE_SHEET];
    const char *files[MAX_FRAMES_SPRITE_SHEET];
} SpriteSheet;

void init_textures();
SpriteSheet *get_sprite_sheet(int id);
