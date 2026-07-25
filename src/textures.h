#pragma once

#include <cpl/cpl.h>

#define MAX_FRAMES_SPRITE_SHEET 8

enum {
    SPRITE_SHEET_RIFLE = 0,
    SPRITE_SHEET_BULLET,
    SPRITE_SHEET_PLAYER_IDLE,
    SPRITE_SHEET_PLAYER_GUN_IDLE,
    SPRITE_SHEET_PLAYER_WALK,
    SPRITE_SHEET_PLAYER_GUN_WALK,
    SPRITE_SHEET_PLAYER_JUMP,
    SPRITE_SHEET_PLAYER_GUN_JUMP,
    SPRITE_SHEET_POLICE_BATON_IDLE,
    SPRITE_SHEET_DOR,
    TOTAL_SPRITE_SHEETS,
};

typedef struct {
    int count;
    float dt;
    texture textures[MAX_FRAMES_SPRITE_SHEET];
    const char *files[MAX_FRAMES_SPRITE_SHEET];
} sprite_sheet_t;

void init_textures();
sprite_sheet_t *get_sprite_sheet(int id);
