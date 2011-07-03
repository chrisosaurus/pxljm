#include "server.hpp"

#include <string>
#include <iostream>
#include <fstream>

Server::Server(unsigned short listening_port, int num_clients)
  : port(listening_port),
  clients(num_clients)
{
}

Server::~Server()
{
  listener.Close();
  selector.Clear();
}

std::string Server::get_error()
{
  return error;
}

bool Server::run()
{
  std::cout << "Trying to listen on port " << port << std::endl;
  if (listener.Listen(port) != sf::Socket::Done)
  {
    ++port;
    std::cout << "Failed, trying to listen on port " << port << std::endl;
    if (listener.Listen(port) != sf::Socket::Done)
    {
      ++port;
      std::cout << "Failed, trying to listen on port " << port << std::endl;
      if (listener.Listen(port) != sf::Socket::Done)
      {
        error = "Error: Could not create socket.";
        return false;
      }
    }
  }
  int clients_so_far = 0;
  std::cout << "Waiting for " << clients << " client(s)" << std::endl;
  selector.Add(listener);

  //while there still clients to connect
  while (clients_so_far < clients)
  {
    if (selector.Wait())
    {
      if (selector.IsReady(listener))
      {
        // there is a client waiting to connect
        sf::TcpSocket *client = new sf::TcpSocket;
        if (listener.Accept(*client) == sf::Socket::Done)
        {
          client_list.push_back(client);
          selector.Add(*client);
          ++clients_so_far;
          std::cout << "Client " << clients_so_far << " connected from " << client->GetRemoteAddress() << std::endl;
        }
      }
    }
  }
  std::cout << "All clients have connected. Sending ready queries..." << std::endl;

  sf::Packet ready_message;
  std::string message = "Ready";
  ready_message.Clear();

  for (int i = 0; i < client_list.size(); ++i)
  {
    std::cout <<  "Sending query to client " << i << std::endl;
    ready_message << message << i;
    client_list[i]->Send(ready_message);
    ready_message.Clear();
  }

  // Wait for ready responses
  int ready = 0;
  while (ready < clients)
  {
    if (selector.Wait())
    {
      for (int i = 0; i < client_list.size(); ++i)
      {
        sf::TcpSocket *client_sending = client_list[i];
        if (selector.IsReady(*client_sending))
        {
          client_sending->Receive(ready_message);
          if ((ready_message >> message) && (message == "Ready"))
          {
            std::cout << "Client " << i + 1 << " is ready" << std::endl;
            ++ready;
          }
        }
      }
    }
  }

  //generate_map("new.map", 7, 10);
  // Send planets
  parse_planet_file("test.map");

  // Send players
  sf::Packet player;
  for (int i = 0; i < client_list.size(); ++i)
  {
    // send all players 
    int x, y;
    // FIXME hard-coded mothership coords
    x = 500 - i*100;
    y = 400 - i*50;
    player.Clear();
    player << x << y << i;
    
    std::cout << "Sending player at " << x << ", " << y << ", uid:" << i << std::endl;
    for (int j = 0; j < client_list.size(); ++j)
    {
      client_list[j]->Send(player);
    }
  }
  player.Clear();
  for (int i = 0; i < client_list.size(); ++i)
  {
    player << -1 << -1 << -1;
    client_list[i]->Send(player);
  }

  // Main loop yay
  while (true)
  {
    if (selector.Wait())
    {
      //std::cout << "Yay got a packet!!" << std::endl;
      
      //if someone else tries to connect, actively kick them
      if (selector.IsReady(listener))
      {
        sf::TcpSocket rejected_client;
        listener.Accept(rejected_client);
        rejected_client.Disconnect();
      }

      for (int i = 0; i < client_list.size(); ++i)
      {
        sf::TcpSocket *client_sending = client_list[i];
        if (selector.IsReady(*client_sending))
        {
          sf::Packet packet_to_receive, packet_to_forward;
          int packet_id, from_id, to_id, timestamp;
          client_sending->Receive(packet_to_receive);
          packet_to_forward = packet_to_receive;
          if (packet_to_receive >> packet_id)
          {
            if (packet_id == 2)
            {
              packet_to_receive >> from_id >> to_id >> timestamp;
              std::cout << "Got a fleet" << std::endl;
              if (timestamp < 0)
              {
                std::cout << "It's a quit fleet" << std::endl;
                selector.Clear();
                listener.Close();
                std::cout << "Client quit. Closing server nicely" << std::endl;
                return true;
              }
            }
          }
          for (int j = 0; j < client_list.size(); ++j)
          {
            if (client_list[j] == client_sending)
            {
              //std::cout << "Skipping player" << j << " who is player " << i << std::endl;
              continue;
            }
            client_list[j]->Send(packet_to_forward);
          }
        }
      }
    }
  }
}

void Server::parse_planet_file(const char *fname = "planets.map"){
  int x, y, rad;
  std::ifstream input(fname);
  while( input >> x >> y >> rad )
  {
    std::cout << "Sending " << x << ", " << y << ", " << rad << std::endl;
    planet(x,y,rad);
  }
  planet(-1, -1, -1);
}

void Server::parse_moship_file(const char *fname = "moships.map")
{
  int x, y;
  std::ifstream input(fname);
  while (input >> x >> y)
  {
    std::cout << "Sending moship " << x << ", " << y << std::endl;
    moship(x, y);
  }
  moship(-1, -1);
}

void Server::moship(int x, int y)
{
  sf::Packet moship_to_send;
  for (int i = 0; i < client_list.size(); ++i)
  {
    moship_to_send << x << y;
    client_list[i]->Send(moship_to_send);
    moship_to_send.Clear();
  }
}

void Server::planet(int x, int y, int rad)
{
  sf::Packet planet_to_send;
  for (int i = 0; i < client_list.size(); ++i)
  {
    planet_to_send << x << y << rad;
    client_list[i]->Send(planet_to_send);
    planet_to_send.Clear();
  }
}
