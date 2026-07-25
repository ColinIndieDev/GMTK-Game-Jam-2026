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
            const char *filename = s->files[j];
            int filename_len = (int)strlen(filename);
            int prefix_len = strlen("assets/images/");

            // add prefix "assets/images/"
            char buf[prefix_len + filename_len + 1];
            strcpy(buf, "assets/images/");
            strcpy(buf + prefix_len, filename);
            buf[prefix_len + strlen(filename)] = '\0';

            // @Yan Why do you print the len of the buffer?
            // - Sorry I forgot to clean up debug prints
            texture_load(&s->textures[j], buf, FILTER_NEAREST);
        }
    }
}

sprite_sheet_t *get_sprite_sheet(int id) {
    assert(0 <= id && id < TOTAL_SPRITE_SHEETS);
    return &sprite_sheets[id];
}
