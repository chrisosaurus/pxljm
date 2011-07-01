class ClientGame {
      public:
        ClientGame();

        ~ClientGame();

        /**
         * Send a fleet of the specified amount from the source planet, heading towards a destination planet.
         */
        void launchFleet(Planet &src, Planet &dest, int count);

        /**
         * Find a planet based on id
         */
        Planet *planetFromId(int id);

        /**
         * Find the closest planet to a specified location.
         * If limit is specified, do not return a Planet further away than the squareroot of this.
         */
        Planet *findNearestPlanet(int x, int y, int limit = 0);
};
