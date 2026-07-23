#include "textures.h"

texture textures[TOTAL_TEXTURES];

char *texture_paths[TOTAL_TEXTURES] = {
    "assets/images/rifle.png",
    "assets/images/bullet.png",
    "assets/images/player_idle0.png",
    "assets/images/player_idle1.png",
    "assets/images/player_gunidle0.png",
    "assets/images/player_gunidle1.png",
    "assets/images/walking/walking_0.png",
    "assets/images/walking/walking_1.png",
    "assets/images/walking/walking_2.png",
    "assets/images/walking/walking_3.png",
};

void init_textures() {
    for (uint32_t i = 0; i < TOTAL_TEXTURES; i++) {
        texture_load(&textures[i], texture_paths[i], FILTER_NEAREST);
    }
}

texture *get_texture(int id) {
    assert(id >= 0 && id < TOTAL_TEXTURES);
    return &textures[id];
}
