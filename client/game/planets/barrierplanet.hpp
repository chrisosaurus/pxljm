#ifndef BARRIERPLANET_H
#define BARRIERPLANET_H
#include "../planet.hpp"

class BarrierPlanet : public Planet {
    BarrierPlanet(int vx, int vy, int vradius, int vid);

    ~BarrierPlanet();

    void ships_arrival(Player *owner, int amount);

    Fleet *launch_fleet(Planet &dest);
};
#endif
