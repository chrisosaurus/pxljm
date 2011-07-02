#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>

class Fleet;
class Player;

class Planet {
protected:
    int x;
    int y;
    const int capacity;

    const int id;

    int last_tick;
    int last_ships;

    Player *owner;
    
    void set_ship_count(int current_time, int ship_count);

public:
    Planet(int vx, int vy, int vcapacity, int vid);
    
    ~Planet();
    
    int get_x() const;

    int get_y() const;
    
    virtual int get_radius() const;

    virtual int get_ship_count(int current_time) const;

    int get_id() const;

    const Player * const get_player() const;
    
    virtual void ships_arrival(Player *player, int amount, int current_time);

    virtual Fleet *launch_fleet(Planet &dest, int launch_time);

    virtual void draw(sf::RenderWindow &window, const sf::Color &c) const;
};

#endif
