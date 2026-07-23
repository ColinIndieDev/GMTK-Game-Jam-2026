#include "player.h"
#include "textures.h"
#include <cpl/cpl.h>
#include <cpstd/mathplus.h>

float anim_timer = 0.0f;
float anim_dt = 0.25f;

// clang-format off
player_t player = {
    .pos = VEC2F(0, 0),
    .size = VEC2F(100, 100),
    .last_velocity = VEC2F(0, 0),
    .velocity = VEC2F(0, 0),
    .move_speed = 100.0f,
    .anim_state = PLAYER_ANIM_IDLE0,
    .has_weapon = false
};
// clang-format on

void init_player() { anim_timer = get_time(); }

void update_player() {
    // Update Animation
    if (anim_timer + anim_dt <= get_time()) {
        player.anim_state = (player.anim_state + 1) % TOTAL_PLAYER_ANIM_STATES;
        anim_timer = get_time();
    }

    // Update Key Inputs
    player.velocity = VEC2F(0, 0);
    if (is_key_down(KEY_LETTER_W)) {
        player.velocity.y = -player.move_speed;
        player.last_velocity = player.velocity;
    }
    if (is_key_down(KEY_LETTER_S)) {
        player.velocity.y = player.move_speed;
        player.last_velocity = player.velocity;
    }
    if (is_key_down(KEY_LETTER_A)) {
        player.velocity.x = -player.move_speed;
        player.last_velocity = player.velocity;
    }
    if (is_key_down(KEY_LETTER_D)) {
        player.velocity.x = player.move_speed;
        player.last_velocity = player.velocity;
    }

    // Update Position
    player.velocity = vec2f_float_mul(player.velocity, get_dt());
    player.pos = vec2f_add(player.pos, player.velocity);
}

void draw_player() {
    vec2f pivot = VEC2F(player.size.x * 0.25f, player.size.y * 0.25f);
    vec3f rotation = (((player.velocity.x == 0.0f) ? player.last_velocity.x : player.velocity.x) > 0.0f) ? VEC3F(0, 0, 0) : VEC3F(0, 180, 0);
    if (player.anim_state == PLAYER_ANIM_IDLE0) {
        texture *player_texture = player.has_weapon ? get_texture(TEXTURE_PLAYER_GUN_IDLE0) : get_texture(TEXTURE_PLAYER_IDLE0);
        draw_texture2D(player_texture, player.pos, player.size, WHITE, rotation, pivot);
    } else {
        texture *player_texture = player.has_weapon ? get_texture(TEXTURE_PLAYER_GUN_IDLE1) : get_texture(TEXTURE_PLAYER_IDLE1);
        draw_texture2D(player_texture, player.pos, player.size, WHITE, rotation, pivot);
    }
}
