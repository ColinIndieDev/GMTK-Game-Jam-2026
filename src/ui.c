#include "ui.h"
#include "player.h"
#include "textures.h"
#include <cpl/cpl.h>

void draw_ui(player_t *player, font *f, int level) {
    vec2f start_pos = VEC2F(10, 10);

    for (uint32_t i = 0; i < MAX_AMMO; i++) {
        color_t color = (i >= player->ammo_loaded) ? BLACK : WHITE;
        draw_texture2D(get_sprite_sheet(SPRITE_SHEET_BULLET)->textures, VEC2F(start_pos.x + (i * 20), start_pos.y), VEC2F(150, 150), color,
                       NO_ROTATION);
    }

    begin_draw(TEXT, false);

    if (player->ammo_stored > 0) {
        draw_text_shadow(f, VEC2F(start_pos.x + (MAX_AMMO * 20) - 5, 80), 1.2f, WHITE, VEC2F(3, 3), BLACK, "+%d", player->ammo_stored);
    }

    draw_text_shadow(f, VEC2F(10, get_screen_height() - 80), 1.7f, WHITE, VEC2F(5, 5), BLACK, "Time left: %.1fs", get_time_left());

    draw_text(f, VEC2F(600, 0), 1.2f, BLACK, "Level %d", level);
}
