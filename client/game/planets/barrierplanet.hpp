class BarrierPlanet : public Planet {
    BarrierPlanet();

    ~BarrierPlanet();

    void remove_ships(int amount);

    Fleet *launch_fleet();
};
