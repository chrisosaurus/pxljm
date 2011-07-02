#include "client.hpp"
#include "../game/game.hpp"
#include "../game/planet.hpp"

Client::Client(const char *server_ip_address, unsigned short server_port, ClientGame *client_game)
  : server_ip(server_ip_address),
  port(server_port),
  game(client_game)
{
}

int Client::join()
{
  if (client.Connect(server_ip, port) != sf::Socket::Done)
  {
    std::cout << "Could not connect to server :-(" << std::endl;
    error = "Could not connect to server.";
    throw error;
  }
  std::cout << "Waiting for ready message" << std::endl;
  sf::Packet ready_message;
  std::string message;
  int player_id;

  client.Receive(ready_message);
  if ((ready_message >> message >> player_id) && (message == "Ready"))
  {
    std::cout << "Received ready message. I am player #" << player_id << ". Sending reply." << std::endl;
    ready_message.Clear();
  }
  else
  {
    std::cout << "Couldn't extract data. Something's gone wrong. It's best if I close now." << std::endl;
    throw error;
  }

  message = "Ready";
  ready_message << message;
  client.Send(ready_message);

  bool planet_end = false;
  int x, y, radius, id;
  sf::Packet planet;

  while(!planet_end)
  {
    client.Receive(planet);
    if (!(planet >> x >> y >> radius))
    {
      if (radius < 0)
      {
        //it's a planet end packet, stop receiving planets
        planet_end = true;
      }
      else
      {
        //it's a regular planet, add it
        game->add_planet(new Planet(x, y, radius, id));
        ++id;
      }
    }
  }

  return player_id;
}

bool Client::send_fleet(Fleet *fleet_to_send)
{
  // TODO: send the fleet to server
}
