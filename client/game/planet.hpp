class Planet {
public:
    Planet();
    
    ~Planet();
    
    int get_x() const;

    int get_y() const;

    int get_ship_count() const;

    /**
     * Removes ships (for instance, when this Planet is being attacked by a fleet)
     * @param amount The amount of attacking ships to be processed at this instant
     */
    void remove_ships(int amount);

    virtual Fleet *launch_fleet();
    
    virtual void logic();
};
