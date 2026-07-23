#pragma once

#include <cpl/cpl.h>

enum {
    PLAYER_ANIM_IDLE0 = 0,
    PLAYER_ANIM_IDLE1,
    TOTAL_PLAYER_ANIM_STATES
};

typedef struct {
    vec2f pos;
    vec2f size;
    vec2f collider_size;
    vec2f velocity;
    float collider_pos_off_x;
    int last_dir_x;
    float move_speed;
    int anim_state;
    bool has_weapon;
    bool ground;
} player_t;

void init_player();
void update_player(int level);
void draw_player();
