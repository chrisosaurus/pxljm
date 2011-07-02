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
#define BENS_WORK_DONE 0
// default ip to connect to, could be 127.0.0.1 later. for now link to server
#define DEFAULTIP "10.1.1.104"

Player *local_player = 0;

int main(int argc, char *argv[]){
  const char *ip = DEFAULTIP;
  if(argc > 1)
    ip = argv[1];
#if BENS_WORK_DONE
  // this is used so I can show the expected interface without loosing the ability to make
  GameClient ga(ip); // need to give a server ip and be able to get a player out of this. ga also needs to call draw
  Interfacing in(ga, ga.get_player());
  in.main();
#endif
}
