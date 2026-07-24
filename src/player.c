#include "player.h"
#include "textures.h"
#include "map.h"
#include <cpl/cpl.h>
#include <cpstd/mathplus.h>

float anim_timer = 0.0f;
float anim_dt = 0.25f;

#define GRAVITY_FORCE 900.0f
#define MAX_FALL_SPEED 1100.0f
#define JUMP_FORCE 450.0f

player_t player = {
    .pos = VEC2F(0, 0),
    .size = VEC2F(100, 100),
    .collider_size = VEC2F(22, 92),
    .velocity = VEC2F(0, 0),
    .collider_pos_off_x = 14.0f,
    .last_dir_x = 1,
    .move_speed = 100.0f,
    .sprite_sheet = SPRITE_SHEET_PLAYER_IDLE,
    .sprite_idx = 0,
    .has_weapon = true,
    .ground = false,
};

void init_player() { anim_timer = get_time(); }

void move_and_collide(tilemap *map) {
    float dt = get_dt();

    player.pos.x += player.velocity.x * dt;

    vec2f player_pos = VEC2F(player.pos.x + player.collider_pos_off_x, player.pos.y);

    uint32_t tile_count = map->renderer.count / 6;
    for (uint32_t t = 0; t < tile_count; t++) {
        if (!map->renderer.collidable[t]) {
            continue;
        }

        vec2f tile_pos = VEC2F(map->renderer.vertices[(uint64_t)t * 6].x, map->renderer.vertices[(uint64_t)t * 6].y);

        if (player.pos.y + player.collider_size.y <= tile_pos.y || player.pos.y >= tile_pos.y + TILE_SIZE) {
            continue;
        }

        rect_collider player_collider = {
            .pos = player_pos,
            .size = player.collider_size,
        };
        rect_collider tile_collider = {
            .pos = tile_pos,
            .size = VEC2F(TILE_SIZE, TILE_SIZE),
        };

        if (check_collision_rects(player_collider, tile_collider)) {
            if (player.velocity.x > 0) {
                player.pos.x = tile_pos.x - player.collider_size.x - 0.01f - player.collider_pos_off_x;
            } else if (player.velocity.x < 0) {
                player.pos.x = tile_pos.x + TILE_SIZE + 0.01f - player.collider_pos_off_x;
            }
            player.velocity.x = 0;
        }
    }

    player.pos.y += player.velocity.y * dt;
    player.ground = false;

    player_pos = VEC2F(player.pos.x + player.collider_pos_off_x, player.pos.y);

    for (uint32_t t = 0; t < tile_count; t++) {
        if (!map->renderer.collidable[t]) {
            continue;
        }

        vec2f tile_pos = VEC2F(map->renderer.vertices[(uint64_t)t * 6].x, map->renderer.vertices[(uint64_t)t * 6].y);

        if (player_pos.x + player.collider_size.x <= tile_pos.x || player_pos.x >= tile_pos.x + TILE_SIZE) {
            continue;
        }

        rect_collider player_collider = {
            .pos = player_pos,
            .size = player.collider_size,
        };
        rect_collider tile_collider = {
            .pos = tile_pos,
            .size = VEC2F(TILE_SIZE, TILE_SIZE),
        };

        if (check_collision_rects(player_collider, tile_collider)) {
            if (player.velocity.y > 0) {
                player.pos.y = tile_pos.y - player.collider_size.y - 0.01f;
                player.ground = true;
            } else if (player.velocity.y < 0) {
                player.pos.y = tile_pos.y + TILE_SIZE + 0.01f;
            }
            player.velocity.y = 0;
        }
    }
}

void update_player(int level) {
    // Update Animation
    if (anim_timer + anim_dt <= get_time()) {
        player.sprite_idx = (player.sprite_idx + 1) % get_sprite_sheet(player.sprite_sheet)->count;
        anim_timer = get_time();
    }

    // Set Camera
    get_cam_2D()->pos.x = player.pos.x + player.collider_pos_off_x + (player.collider_size.x * 0.5f) - ((float)get_screen_width() * 0.5f);

    // Update Key Inputs
    if (is_key_down(KEY_LETTER_A)) {
        player.velocity.x = -player.move_speed;
        player.last_dir_x = -1;
    } else if (is_key_down(KEY_LETTER_D)) {
        player.velocity.x = player.move_speed;
        player.last_dir_x = 1;
    } else if (player.ground) {
        player.velocity.x = 0.0f;
    }
    if (is_key_down(KEY_SPACE) && player.ground) {
        player.velocity.y = -JUMP_FORCE;
        player.ground = false;
    }

    // toggle player's gun with "g" key
    if (is_key_pressed(KEY_LETTER_G)) {
        if (player.has_weapon) {
            hide_gun_player();
        } else {
            show_gun_player();
        }
    }

    player.velocity.y += GRAVITY_FORCE * get_dt();
    if (player.velocity.y > MAX_FALL_SPEED) {
        player.velocity.y = MAX_FALL_SPEED;
    }

    // Update Position
    move_and_collide(get_level_tilemap(level));
}

void draw_player() {
    vec2f pivot = VEC2F(player.size.x * 0.25f, player.size.y * 0.25f);
    vec3f rotation = (player.last_dir_x > 0) ? VEC3F(0, 0, 0) : VEC3F(0, 180, 0);
    texture *player_texture = &get_sprite_sheet(player.sprite_sheet)->textures[player.sprite_idx];
    draw_texture2D(player_texture, player.pos, player.size, WHITE, rotation, pivot);
}

void show_gun_player() {
    player.has_weapon = true;
    player.sprite_idx = 0;
    player.sprite_sheet = SPRITE_SHEET_PLAYER_GUN_IDLE;
}

void hide_gun_player() {
    player.has_weapon = false;
    player.sprite_idx = 0;
    player.sprite_sheet = SPRITE_SHEET_PLAYER_IDLE;
}
