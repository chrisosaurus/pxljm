#ifndef PLANET_H
#define PLANET_H
class Fleet;
class Player;

class Planet {
private:
    const int x;
    const int y;
    const int radius;

    const int id;

    int ships;

    Player *owner;
    
public:
    Planet(int vx, int vy, int vradius, int vid);
    
    ~Planet();
    
    int get_x() const;

    int get_y() const;
    
    int get_radius() const;

    int get_ship_count() const;

    int get_id() const;

    const Player * const get_player() const;
    
    virtual void ships_arrival(Player *player, int amount);

    virtual Fleet *launch_fleet(Planet &dest, int timestamp);
    
    virtual void logic();
};

#endif
