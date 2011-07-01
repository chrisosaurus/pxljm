#include "barrierplanet.hpp"

BarrierPlanet::BarrierPlanet(int vx, int vy, int vradius, int vid)
    : Planet(vx, vy, vradius, vid) {}

BarrierPlanet::~BarrierPlanet() {}

void BarrierPlanet::ships_arrival(Player *owner, int amount) {
    /* FIXME TODO */
}

Fleet *BarrierPlanet::launch_fleet(Planet &dest) {
    /* FIXME TODO */
}
