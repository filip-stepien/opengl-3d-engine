#ifndef LEVEL_H
#define LEVEL_H

#include "Engine.hpp"
#include "Asset.hpp"

namespace demo {
    const int VENT_COUNT = 4;
    const int WALL_COUNT = 4;
    const int LIGHT_COUNT = 2;
    const float INITIAL_SPAWN_RADIUS = 5.0f;
    const float LEVEL_RADIUS = 10.0f;

    class Level : public Asset {
    private:
        Model vents[VENT_COUNT];
        Light light[LIGHT_COUNT];
        Plane3D ventPlanes[VENT_COUNT];
        Plane3D walls[WALL_COUNT];
        Plane3D lightSource[LIGHT_COUNT];
        Plane3D floor;
        Plane3D roof;

    public:
        void createVents();
        void createLight(int index, float x, float z);
        void createWalls();
        void createFloor();
        void createRoof();
        void create() override;
    };
}
#endif