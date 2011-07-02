#include "client.hpp"
#include "../game/game.hpp"
#include "../game/planet.hpp"
#include "../game/player.hpp"

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

  // Receive all planets
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

  // Receive all players/moships
  sf::Packet player;
  bool player_end = false;
  int uid;
  while (!player_end)
  {
    client.Receive(player);
    if (player >> x >> y >> uid)
    {
      if (uid < 0)
      {
        // It's a player end packet, stop receiving players
        player_end = true;
        std::cout << "Got end packet" << std::endl;
      }
      else
      {
        // it's a regular player, add it
        std::cout << "Adding mothership at " << x << ", " << y << ", id:" << id << std::endl;
        Player *new_player = new Player(uid);
        new_player->set_moship(new Mothership(x, y, id));
        ++id;
        game->add_player(new_player);
        game->add_planet(new_player->get_moship());
      }
    }
  }

  client.SetBlocking(false);
  return player_id;
}

bool NetworkingClient::receive_packet()
{
  sf::Packet received_fleet;
  int packet_id;

  if (client.Receive(received_fleet) != sf::Socket::Done)
  {
    return false;
  }
  received_fleet >> packet_id;
  if (packet_id == 1)
  {
    //TODO moship
  }
  else if(packet_id == 2)
  {
    // fleet
    std::cout << "Fleet Packet" << std::endl;
    int from_id, to_id, timestamp;

    if (!(received_fleet >> from_id >> to_id >> timestamp))
    {
      std::cout << "Error extracting data from Packet" << std::endl;
      error = "Error extracting data from Packet";
      throw error;
    }
    if (timestamp < 0)
    {
      std::cout << "Received quit command" << std::endl;
      client.Disconnect();
      return true;
    }
    game->launch_fleet(from_id, to_id, timestamp);
  }
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
  if (!(fleet_to_send << 2 << from_id << to_id << timestamp))
  {
    std::cout << "Error putting fleet data into Packet." << std::endl;
    error = "Error putting fleet data into Packet";
    throw error;
  }
  client.Send(fleet_to_send);
  return true;
}

bool NetworkingClient::send_moship(int moship_id, int timestamp, int x_dest, int y_dest)
{
  sf::Packet moship_to_move;
  int id, time, x, y;
  moship_to_move << 1 << id << time << x << y;

}






