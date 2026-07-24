#pragma once

#include <cpl/cpl.h>

typedef struct {
    vec2f pos;
    vec2f size;
    vec2f collider_size;
    vec2f velocity;
    float collider_pos_off_x;
    int last_dir_x;
    float move_speed;
    int sprite_sheet;
    int sprite_idx;
    bool has_weapon;
    bool ground;
} player_t;

void init_player();
void update_player(int level);
void draw_player();
void show_gun_player();
void hide_gun_player();
