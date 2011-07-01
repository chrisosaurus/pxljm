#ifndef PLANET
#define PLANET
class Fleet;

class Planet {
private:
    const int x;
    const int y;
    const int radius;

    const int id;
    
public:
    Planet(int vx, int vy, int vradius, int vid);
    
    ~Planet();
    
    int get_x() const;

    int get_y() const;
    
    int get_radius() const;

    int get_ship_count() const;

    int get_id() const;

    /**
     * Removes ships (for instance, when this Planet is being attacked by a fleet)
     * @param amount The amount of attacking ships to be processed at this instant
     */
    virtual void remove_ships(int amount);

    virtual Fleet *launch_fleet(Planet &dest);
    
    virtual void logic();
};

#endif
