#include "fleet.hpp"
#include "player.hpp"

#include "planet.hpp"

Planet::Planet(int vx, int vy, int vcapacity, int vid) : x(vx), y(vx), capacity(vcapacity), id(vid), ships(0), tick(1), owner(0) { }

Planet::~Planet() {}

int Planet::get_x() const { return x; }
int Planet::get_y() const { return y; }

int Planet::get_radius() const { return 30 + (capacity >> 1); }

int Planet::get_id() const { return id; }

const Player * const Planet::get_player() const { return owner; }

void Planet::set_ship_count(int current_time, int ship_count) {
    last_ships = ship_count;
    last_tick = current_time;
}

int Planet::get_ship_count(int current_time) const {
    if (current_time == last_tick)
        return last_ships;
    int ships = last_ships + (current_time - last_tick >> 7);
    if (ships > capacity)
        ships = capacity;
    return ships;
}

void Planet::ships_arrival(Player *player, int amount, int current_time) {
    if (player == owner) {
        /* Reinforcements */
        set_ship_count(current_time, std::min(capacity, get_ship_count(current_time) + amount));
    } else {
        /* Assault */
        int ships = get_ship_count() - amount;
        if (ships < 0) {
            ships = -ships;
            owner = player;
        }
        set_ship_count(current_time, ship_count);
    }
}

Fleet *Planet::launch_fleet(Planet &dest, int launch_time) {
    /* Always send half the available amount. */
    int ships = get_ship_count();
    Fleet *f = new Fleet(ships >> 1, *this, dest, launch_time, *owner);
    set_ship_count(launch_time, ships - ships >> 1);
    return f;
}
