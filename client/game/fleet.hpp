
class Planet;
class Player;

class Fleet {
public:
  
  std::vector<Ship*> ships;
  
  int startTime; // in millis
  float radius;
  
  Planet &orig;  // origin
  Planet &dest;  // destination
  
  Player &owner;

  Fleet(int quantity, Planet &origin, Planet &destination, int launchTime);
  
  bool update(int viewerX, int viewerY, int gameTime, int frameTime);
};


