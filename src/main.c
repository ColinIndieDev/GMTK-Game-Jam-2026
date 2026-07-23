#define CPL_IMPL
#include <cpl/cpl.h>

int main(void) {
    window_init(800, 800, "GMTK Game", OPENGL_VER_3_3);

    font f;
    font_load(&f, "assets/fonts/default.ttf", "default", FILTER_NEAREST);

    while (!window_should_close()) {
        update();

        clear_background(BLACK);
        begin_draw(TEXT, false);
        draw_text(&f, VEC2F(get_screen_width() * 0.5f, get_screen_height() * 0.5f), 1, WHITE, "Hello, World!");
        end_frame();
    }
    window_close();
}
