#ifndef PLANET_H
#define PLANET_H
class Fleet;
class Player;

class Planet {
private:
    const int x;
    const int y;
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
    
    int get_radius() const;

    virtual int get_ship_count(int current_time) const;

    int get_id() const;

    const Player * const get_player() const;
    
    virtual void ships_arrival(Player *player, int amount, int current_time);

    virtual Fleet *launch_fleet(Planet &dest, int launch_time);
};

#endif
