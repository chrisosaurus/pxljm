#include "fleet.hpp"
#include "player.hpp"

#include "planet.hpp"

Planet::Planet(int vx, int vy, int vradius, int vid) : x(vx), y(vx), radius(vradius), id(vid), ships(0), owner(0) { }

Planet::~Planet() {}

int Planet::get_x() const { return x; }
int Planet::get_y() const { return y; }

int Planet::get_radius() const { return radius; }

int Planet::get_id() const { return id; }

const Player * const Planet::get_player() const { return owner; }

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

Fleet *Planet::launch_fleet(Planet &dest, int timestamp) {
    /* Always send half the available amount. */
    Fleet *f = new Fleet(ships >> 1, *this, dest, timestamp, *owner);
    ships -= ships >> 1;
    return f;
}

void Planet::logic() {
    /* How should this be done? Limiting towards some maximum capacity passed in to the constructor? Should the radius be made dependant on such a value for capacity? */
    /* TODO FIXME */
}
