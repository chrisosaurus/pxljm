class Planet {
public:
    Planet();
    
    ~Planet();
    
    int getX() const;

    int getY() const;

    int getShipCount() const;

    void removeShips(int amount);

    virtual void logic();
};
