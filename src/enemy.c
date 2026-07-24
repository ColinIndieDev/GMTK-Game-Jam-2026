#include "enemy.h"
#include "textures.h"

void update_enemy(enemy_t *enemy) {
    // Update Animation
    if (enemy->anim_timer + enemy->anim_dt <= get_time()) {
        enemy->sprite_idx = (enemy->sprite_idx + 1) % get_sprite_sheet(enemy->sprite_sheet)->count;
        enemy->anim_timer = get_time();
    }
}

void draw_enemy(enemy_t *enemy) {
    texture *enemy_texture = &get_sprite_sheet(enemy->sprite_sheet)->textures[enemy->sprite_idx];
    draw_texture2D(enemy_texture, enemy->pos, enemy->size, WHITE, NO_ROTATION);
}
