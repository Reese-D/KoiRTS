#include "../include/spatial_hash.h"
#include <stdlib.h>
#include <math.h>

typedef struct Entry {
    uint64_t entity_id;
    float x;
    float y;
    struct Entry *next;
} Entry;

struct SpatialHash {
    float cell_size;
    int capacity;
    Entry **buckets;
};

static int cell_key(const SpatialHash *sh, int cx, int cy) {
    return ((cx * 1327) ^ (cy * 9001)) & (sh->capacity - 1);
}

SpatialHash *spatial_hash_create(float cell_size, int capacity) {
    SpatialHash *sh = malloc(sizeof(SpatialHash));
    sh->cell_size = cell_size;
    sh->capacity = capacity;
    sh->buckets = calloc(capacity, sizeof(Entry *));
    return sh;
}

void spatial_hash_destroy(SpatialHash *sh) {
    spatial_hash_clear(sh);
    free(sh->buckets);
    free(sh);
}

void spatial_hash_clear(SpatialHash *sh) {
    for (int i = 0; i < sh->capacity; i++) {
        Entry *e = sh->buckets[i];
        while (e) {
            Entry *next = e->next;
            free(e);
            e = next;
        }
        sh->buckets[i] = NULL;
    }
}

void spatial_hash_insert(SpatialHash *sh, uint64_t entity_id, float x, float y) {
    int cx = (int)floorf(x / sh->cell_size);
    int cy = (int)floorf(y / sh->cell_size);
    int key = cell_key(sh, cx, cy);
    Entry *e = malloc(sizeof(Entry));
    e->entity_id = entity_id;
    e->x = x;
    e->y = y;
    e->next = sh->buckets[key];
    sh->buckets[key] = e;
}

int spatial_hash_query(const SpatialHash *sh, float x, float y, float radius,
                       uint64_t *out_ids, int max_results) {
    int count = 0;
    int min_cx = (int)floorf((x - radius) / sh->cell_size);
    int max_cx = (int)floorf((x + radius) / sh->cell_size);
    int min_cy = (int)floorf((y - radius) / sh->cell_size);
    int max_cy = (int)floorf((y + radius) / sh->cell_size);
    float r2 = radius * radius;

    for (int cx = min_cx; cx <= max_cx && count < max_results; cx++) {
        for (int cy = min_cy; cy <= max_cy && count < max_results; cy++) {
            int key = cell_key(sh, cx, cy);
            for (Entry *e = sh->buckets[key]; e && count < max_results; e = e->next) {
                float dx = e->x - x;
                float dy = e->y - y;
                if (dx * dx + dy * dy <= r2) {
                    out_ids[count++] = e->entity_id;
                }
            }
        }
    }
    return count;
}
