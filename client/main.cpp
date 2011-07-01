// oh god, it burns, IT BURNS!!!!

// stuff for networking
#include "networking/client.hpp"

// stuff for interfacing.hpp
#include "game/ship.hpp"
#include "game/fleet.hpp"
#include "game/planet.hpp"
#include "game/game.hpp"
#include "game/mothership.hpp"
#include "game/player.hpp"
#include "interfacing/interfacing.hpp"

// if set to 1, will include code that will break the current make but is needed in the final version
#define COMPILE 0

int main(){
#if COMPILE
  // this is used so I can show the expected interface without loosing the ability to make
  GameClient ga; // need to give a server ip and be able to get a player out of this. ga also needs to call draw
  Interfacing(ga, ga.get_player()) in;
  in.main();
#endif
}
