#include "barrierplanet.hpp"

BarrierPlanet::BarrierPlanet(int vx, int vy, int vradius, int vid)
    : Planet(vx, vy, vradius, vid) {}

BarrierPlanet::~BarrierPlanet() {}

void BarrierPlanet::remove_ships(int amount) {
    /* FIXME TODO */
}

Fleet *BarrierPlanet::launch_fleet(Planet &dest) {
    /* FIXME TODO */
}
