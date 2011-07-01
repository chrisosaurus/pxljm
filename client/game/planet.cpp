#include "planet.hpp"

Planet::Planet(int vx, int vy, int vradius, int vid) : x(vx), y(vx), radius(vradius), id(vid) { }

Planet::~Planet() {}

int Planet::get_x() const { return x; }
int Planet::get_y() const { return y; }

int Planet::get_radius() const { return radius; }

int Planet::get_id() const { return id; }

void Planet::ships_arrival(Player *player, int amount) {
    if (player == owner) {
        /* Reinforcements */
        ships += amount;
        /* Additional dynamics? Hard cap? */
    } else {
        /* Assault */
        ships -= amount;
        if (ships < 0) {
            ships = -ships;
            owner = player;
        }
    }
    /* TODO FIXME */
}

Fleet *Planet::launch_fleet(Planet &dest) {
    /* Always send half the available amount. */
    Fleet *f = new Fleet(ships >> 1, *this, dest, 0 /* *** FIXME FIXME *** */, owner);
    ships -= ships >> 1;
    return f;
}

void Planet::logic() {
    /* How should this be done? Limiting towards some maximum capacity passed in to the constructor? Should the radius be made dependant on such a value for capacity? */
    /* TODO FIXME */
}
