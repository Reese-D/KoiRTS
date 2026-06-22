#include "flecs_smoke.h"

#include "flecs/flecs.h"

bool koi_flecs_smoke(void) {
    ecs_world_t *world = ecs_init();
    if (!world) {
        return false;
    }

    ecs_fini(world);
    return true;
}
