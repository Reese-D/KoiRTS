#pragma once
#include <stdint.h>

typedef struct SpatialHash SpatialHash;

SpatialHash *spatial_hash_create(float cell_size, int capacity);
void spatial_hash_destroy(SpatialHash *sh);
void spatial_hash_clear(SpatialHash *sh);
void spatial_hash_insert(SpatialHash *sh, uint64_t entity_id, float x, float y);
int spatial_hash_query(const SpatialHash *sh, float x, float y, float radius,
                       uint64_t *out_ids, int max_results);
