#define CPL_IMPL
#include <cpl/cpl.h>

#include "map.h"
#include "textures.h"
#include "player.h"

int cur_level = LEVEL_0;

int main(void) {
    window_init(800, 800, "GMTK Game", OPENGL_VER_3_3);
    font f;
    font_load(&f, "assets/fonts/default.ttf", "default", FILTER_NEAREST);

    init_textures();
    init_player();
    init_levels();

    while (!window_should_close())
    {
        update();

        update_player(cur_level);

        clear_background(LIGHT_GRAY);
        begin_draw(TEXTURE_2D_UNLIT, true);

        draw_level(cur_level);
        draw_player();

        end_frame();
    }
    window_close();
}
