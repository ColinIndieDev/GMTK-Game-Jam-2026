#define CPL_IMPL
#include <cpl/cpl.h>

#include "textures.h"
#include "player.h"

int main(void)
{
    window_init(800, 800, "GMTK Game", OPENGL_VER_3_3);
    font f;
    font_load(&f, "assets/fonts/default.ttf", "default", FILTER_NEAREST);

    init_textures();
    init_player();

    while (!window_should_close())
    {
        update();

        update_player();

        clear_background(GREEN);
        begin_draw(TEXTURE_2D_UNLIT, false);

        draw_player();

        end_frame();
    }
    window_close();
}
