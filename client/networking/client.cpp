#include "client.hpp"
#include "../game/game.hpp"
#include "../game/planet.hpp"

NetworkingClient::NetworkingClient(const char *server_ip_address, unsigned short server_port)
  : server_ip(server_ip_address),
  port(server_port)
{
}

void NetworkingClient::init(ClientGame *client_game)
{
  game = client_game;
}

int NetworkingClient::join()
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
    error = "Couldn't extract data";
    throw error;
  }

  message = "Ready";
  ready_message << message;
  client.Send(ready_message);

  bool planet_end = false;
  int x, y, radius, id = 0;
  sf::Packet planet;

  while(!planet_end)
  {
    client.Receive(planet);
    if (planet >> x >> y >> radius)
    {
      if (radius < 0)
      {
        //it's a planet end packet, stop receiving planets
        planet_end = true;
      }
      else
      {
        //it's a regular planet, add it
        std::cout << "Adding  planet at " << x << ", " << y << ", radius: " << radius << ", id: " << id << std::endl;
        game->add_planet(new Planet(x, y, radius, id));
        ++id;
      }
    }
  }

  client.SetBlocking(false);
  return player_id;
}

bool NetworkingClient::receive_fleet()
{
  sf::Packet received_fleet;
  int from_id, to_id, timestamp;

  if (client.Receive(received_fleet) != sf::Socket::Done)
  {
    return false;
  }

  if (!(received_fleet >> from_id >> to_id >> timestamp))
  {
    std::cout << "Error extracting data from Packet" << std::endl;
    error = "Error extracting data from Packet";
    throw error;
  }
  game->launch_fleet(from_id, to_id, timestamp);
}

bool NetworkingClient::send_fleet(Fleet *fleet)
{
  sf::Packet fleet_to_send;
  int from_id, to_id, timestamp;
  
  if (fleet)
  {
    std::cout << "Valid fleet" << std::endl;
    from_id = fleet->orig.get_id();
    to_id = fleet->dest.get_id();
    timestamp = fleet->startTime;
  }
  else
  {
    std::cout << "Invalid fleet. Quitting" << std::endl;
    from_id = -1;
    to_id = -1;
    timestamp = -1;
  }
  if (!(fleet_to_send << from_id << to_id << timestamp))
  {
    std::cout << "Error putting fleet data into Packet." << std::endl;
    error = "Error putting fleet data into Packet";
    throw error;
  }
  client.Send(fleet_to_send);
  return true;
}
