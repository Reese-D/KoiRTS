#pragma once
#include <stdint.h>

typedef struct {
    float dx;
    float dy;
} FlowVector;

typedef struct {
    FlowVector *vectors;
    int width;
    int height;
} FlowField;

FlowField *flowfield_create(int width, int height);
void flowfield_destroy(FlowField *ff);
void flowfield_compute(FlowField *ff, int *cost_grid, int goal_x, int goal_y);
FlowVector flowfield_sample(const FlowField *ff, float x, float y);
