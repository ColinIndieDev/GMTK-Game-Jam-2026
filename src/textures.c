#include "textures.h"

// clang-format off
#define MAKE_SPRITE_SHEET(...) ((sprite_sheet_t){ \
    .count = sizeof((const char *[]){__VA_ARGS__}) / sizeof(char *), \
    .files = { __VA_ARGS__ },  })
// clang-format on

sprite_sheet_t sprite_sheets[TOTAL_SPRITE_SHEETS] = {
    MAKE_SPRITE_SHEET("rifle.png"),
    MAKE_SPRITE_SHEET("bullet.png"),
    MAKE_SPRITE_SHEET("player_idle0.png", "player_idle1.png"),
    MAKE_SPRITE_SHEET("player_gunidle0.png", "player_gunidle1.png"),
    MAKE_SPRITE_SHEET("player_walking0.png", "player_walking1.png", "player_walking2.png", "player_walking3.png"),
    MAKE_SPRITE_SHEET("police_batonidle0.png", "police_batonidle1.png"),
};

void init_textures() {
    for (uint32_t i = 0; i < TOTAL_SPRITE_SHEETS; i++) {
        sprite_sheet_t *s = &sprite_sheets[i];

        for (uint32_t j = 0; j < s->count; j++) {
            char filename[256];
            sprintf(filename, "assets/images/%s", s->files[j]);
            texture_load(&s->textures[j], filename, FILTER_NEAREST);
        }
    }
}

sprite_sheet_t *get_sprite_sheet(int id) {
    assert(0 <= id && id < TOTAL_SPRITE_SHEETS);
    return &sprite_sheets[id];
}
