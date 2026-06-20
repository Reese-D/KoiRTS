#include "../include/flowfield.h"
#include <stdlib.h>


FlowField *flowfield_create(int width, int height) {
    FlowField *ff = malloc(sizeof(FlowField));
    ff->vectors = calloc(width * height, sizeof(FlowVector));
    ff->width = width;
    ff->height = height;
    return ff;
}

void flowfield_destroy(FlowField *ff) {
    free(ff->vectors);
    free(ff);
}

void flowfield_compute(FlowField *ff, int *cost_grid, int goal_x, int goal_y) {
    (void)cost_grid;
    (void)goal_x;
    (void)goal_y;
    /* TODO: Dijkstra from goal outward over cost_grid, then derive
       gradient vectors for each cell */
}

FlowVector flowfield_sample(const FlowField *ff, float x, float y) {
    int cx = (int)x;
    int cy = (int)y;
    if (cx < 0 || cx >= ff->width || cy < 0 || cy >= ff->height) {
        return (FlowVector){0.0f, 0.0f};
    }
    return ff->vectors[cy * ff->width + cx];
}
