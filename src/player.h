#pragma once

#include <cpl/cpl.h>

// clang-format off
enum {
    PLAYER_ANIM_IDLE0 = 0,
    PLAYER_ANIM_IDLE1,
    TOTAL_PLAYER_ANIM_STATES
};
// clang-format on

typedef struct {
    vec2f pos;
    vec2f size;
    vec2f last_velocity;
    vec2f velocity;
    float move_speed;
    int anim_state;
    bool has_weapon;
} player_t;

void init_player();
void update_player();
void draw_player();
