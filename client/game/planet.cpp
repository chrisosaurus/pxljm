#include "planet.hpp"

Planet::Planet(int vx, int vy, int vradius, int vid) : x(vx), y(vx), radius(50), id(vid) { }

Planet::~Planet() {}

int Planet::get_x() const { return x; }
int Planet::get_y() const { return y; }

int Planet::get_radius() const { return radius; }

int Planet::get_id() const { return id; }

void Planet::remove_ships(int amount) {
    /* TODO FIXME */
}

Fleet *Planet::launch_fleet(Planet &dest) {
    /* TODO FIXME */
    return 0;
}

void Planet::logic() {
    /* TODO FIXME */
}
