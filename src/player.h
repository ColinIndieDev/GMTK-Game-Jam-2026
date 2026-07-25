#pragma once

#include <cpl/cpl.h>

#define GRAVITY_FORCE 900.0f
#define MAX_FALL_SPEED 1100.0f
#define JUMP_FORCE 450.0f

#define MAX_AMMO 5
#define BULLET_VELOCITY 1000.0f
#define BULLET_SIZE VEC2F(15, 5)

#define MAX_TIME_S (15 * 60)

typedef struct {
    vec2f pos;
    vec2f size;
    vec2f collider_size;
    vec2f velocity;
    float collider_pos_off_x;
    int last_dir_x;
    float move_speed;
    int ammo_loaded;
    int ammo_stored;
    int sprite_sheet;
    int sprite_idx;
    bool has_weapon;
    bool ground;
} player_t;

typedef struct {
    vec2f pos;
    vec2f velocity;
    bool active;
} bullet_t;

void init_player();
player_t *get_player();
void update_bullets(int level);
void update_player(int *level);
float get_time_left();
void update_timer();
void draw_player();
void draw_bullets();
void toggle_gun_player();
