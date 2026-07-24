#pragma once

#include <cpl/cpl.h>

typedef struct {
    vec2f pos;
    vec2f size;
    int sprite_sheet;
    int sprite_idx;
    float anim_timer;
    float anim_dt;
} enemy_t;
#define ENEMY(pos, size, dt) (enemy_t){pos, size, SPRITE_SHEET_POLICE_BATON_IDLE, 0, get_time(), dt}

void update_enemy(enemy_t *enemy);
void draw_enemy(enemy_t *enemy);
