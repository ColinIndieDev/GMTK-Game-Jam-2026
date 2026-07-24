#include "map.h"
#include <cpl/cpl.h>
#include <stdio.h>

#define TILEMAP_PATH "assets/images/tilemap.png"

tilemap level_maps[TOTAL_LEVELS];

const char *level_data_paths[TOTAL_LEVELS] = {
    "levels/level0.txt",
};

void load_level_data(int level) {
    FILE *file = fopen(level_data_paths[level], "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot find: %s\n", level_data_paths[level]);
        exit(-1);
    }
    for (;;) {
        vec2f pos = VEC2F(0, 0);
        if (fscanf(file, "%f %f", &pos.x, &pos.y) != 2) {
            fclose(file);
            return;
        }
        tilemap_add_tile(&level_maps[level], pos, VEC2F(TILE_SIZE, TILE_SIZE), VEC2F(0, 0));
    }
    fclose(file);
}

void build_level_map(int level) {
    tilemap *map = &level_maps[level];
    uint32_t tile_count = map->renderer.count / 6;
    for (uint32_t t = 0; t < tile_count; t++) {
        if (!map->renderer.collidable[t]) {
            continue;
        }

        vec2f tile_pos = VEC2F(map->renderer.vertices[(uint64_t)t * 6].x, map->renderer.vertices[(uint64_t)t * 6].y);

        vec2f neighbors[4] = {
            VEC2F(tile_pos.x - TILE_SIZE, tile_pos.y), // LEFT
            VEC2F(tile_pos.x + TILE_SIZE, tile_pos.y), // RIGHT
            VEC2F(tile_pos.x, tile_pos.y - TILE_SIZE), // UP
            VEC2F(tile_pos.x, tile_pos.y + TILE_SIZE), // DOWN
        };

        bool left = tilemap_tile_exists(map, VEC2F(tile_pos.x - TILE_SIZE, tile_pos.y));
        bool right = tilemap_tile_exists(map, VEC2F(tile_pos.x + TILE_SIZE, tile_pos.y));
        bool up = tilemap_tile_exists(map, VEC2F(tile_pos.x, tile_pos.y - TILE_SIZE));
        bool down = tilemap_tile_exists(map, VEC2F(tile_pos.x, tile_pos.y + TILE_SIZE));

        vec2f uv = VEC2F(0, 0);
        if (left && right) {
            uv = VEC2F(1, 0);
        } else if (right) {
            uv = VEC2F(0, 1);
        } else if (left) {
            uv = VEC2F(1, 1);
        }

        float tw = map->size.x / map->tex.size.x;
        float th = map->size.y / map->tex.size.y;

        float u_start = uv.x * tw;
        float v_start = 1.0f - ((uv.y + 1) * th);
        float u_end = u_start + tw;
        float v_end = v_start + th;

        map->renderer.vertices[((uint64_t)t * 6)].u = u_start;
        map->renderer.vertices[((uint64_t)t * 6)].v = v_start;
        map->renderer.vertices[((uint64_t)t * 6) + 1].u = u_end;
        map->renderer.vertices[((uint64_t)t * 6) + 1].v = v_start;
        map->renderer.vertices[((uint64_t)t * 6) + 2].u = u_end;
        map->renderer.vertices[((uint64_t)t * 6) + 2].v = v_end;
        map->renderer.vertices[((uint64_t)t * 6) + 3].u = u_start;
        map->renderer.vertices[((uint64_t)t * 6) + 3].v = v_start;
        map->renderer.vertices[((uint64_t)t * 6) + 4].u = u_end;
        map->renderer.vertices[((uint64_t)t * 6) + 4].v = v_end;
        map->renderer.vertices[((uint64_t)t * 6) + 5].u = u_start;
        map->renderer.vertices[((uint64_t)t * 6) + 5].v = v_end;
    }
}

void init_levels() {
    tilemap_create(&level_maps[LEVEL_0], VEC2F(16, 16));
    tilemap_load_texture(&level_maps[LEVEL_0], TILEMAP_PATH, FILTER_NEAREST);
    tilemap_begin_editing(&level_maps[LEVEL_0]);
    load_level_data(LEVEL_0);
    tilemap_check_collidable_tiles(&level_maps[LEVEL_0], VEC2F(TILE_SIZE, TILE_SIZE));
    build_level_map(LEVEL_0);
}

tilemap *get_level_tilemap(int level) { return &level_maps[level]; }

void draw_level(int level) { tilemap_draw(&level_maps[level], WHITE); }
