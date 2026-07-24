#define CPL_IMPL
#include <cpl/cpl.h>

#include "textures.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "ui.h"

int cur_level = LEVEL_0;

int main(void) {
    window_init(800, 800, "GMTK Game", OPENGL_VER_3_3);
    get_cam_2D()->zoom = 1.75f;
    font f;
    font_load(&f, "assets/fonts/default.ttf", "default", FILTER_NEAREST);

    init_textures();
    init_player();
    init_levels();

    enemy_t e = ENEMY(VEC2F(100, 100), VEC2F(100, 100), 0.25f);

    while (!window_should_close()) {
        update();

        update_player(cur_level);
        update_bullets(cur_level);

        update_enemy(&e);

        clear_background(LIGHT_GRAY);
        begin_draw(SHAPE_2D_UNLIT, true);
        draw_bullets();
        begin_draw(TEXTURE_2D_UNLIT, true);
        draw_level(cur_level);
        draw_player();

        draw_enemy(&e);

        begin_draw(TEXTURE_2D_UNLIT, false);
        draw_ui(get_player(), &f);

        end_frame();
    }
    window_close();
}
