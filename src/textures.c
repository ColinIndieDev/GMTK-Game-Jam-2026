#include "textures.h"

// clang-format off
#define MAKE_SPRITE_SHEET(_dt, ...) ((sprite_sheet_t){               \
    .count = sizeof((const char *[]){__VA_ARGS__}) / sizeof(char *), \
    .files = { __VA_ARGS__ },                                        \
    .dt = _dt,})
// clang-format on

sprite_sheet_t sprite_sheets[TOTAL_SPRITE_SHEETS] = {
    MAKE_SPRITE_SHEET(0.00f, "rifle.png"),
    MAKE_SPRITE_SHEET(0.00f, "bullet.png"),
    MAKE_SPRITE_SHEET(0.25f, "player_idle0.png", "player_idle1.png"),
    MAKE_SPRITE_SHEET(0.25f, "player_gunidle0.png", "player_gunidle1.png"),
    MAKE_SPRITE_SHEET(0.10f, "player_walk0.png", "player_walk1.png", "player_walk2.png"),
    MAKE_SPRITE_SHEET(0.10f, "player_gunwalk0.png", "player_gunwalk1.png", "player_gunwalk2.png"),
    MAKE_SPRITE_SHEET(0.00f, "player_jump.png"),
    MAKE_SPRITE_SHEET(0.00f, "player_gunjump.png"),
    MAKE_SPRITE_SHEET(0.25f, "police_batonidle0.png", "police_batonidle1.png"),
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
