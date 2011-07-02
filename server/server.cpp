#include "server.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include "mapper.hpp" // function to create maps

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
    error = "Error: Could not create socket.";
    return false;
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
  std::cout << "All clients have connected. Sending ready query..." << std::endl;

  sf::Packet ready_message;
  std::string message = "Ready";
  ready_message.Clear();

  for (int i = 0; i < client_list.size(); ++i)
  {
    std::cout << client_list.size() << ", " << i << std::endl;
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


  // Send planets
  parse_file("test.map");


  // Main loop yay
  while (true)
  {
    if (selector.Wait())
    {
      std::cout << "Yay got a packet!!" << std::endl;
      for (int i = 0; i < client_list.size(); ++i)
      {
        sf::TcpSocket *client_sending = client_list[i];
        if (selector.IsReady(*client_sending))
        {
          sf::Packet fleet_to_receive;
          int from_id, to_id, timestamp;
          client_sending->Receive(fleet_to_receive);
          if (fleet_to_receive >> from_id >> to_id >> timestamp)
          {
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
          for (int j = 0; j < client_list.size(); ++j)
          {
            if (client_list[j] == client_sending)
            {
              continue;
            }
            fleet_to_receive.Clear();
            fleet_to_receive << from_id << to_id << timestamp;
            client_list[j]->Send(fleet_to_receive);
          }
        }
      }
    }
  }
}

void Server::parse_file(const char *fname = "test.map"){
  int x,y,rad,owner;
  std::ifstream input(fname);
  while( input >> x >> y >> rad >> owner )
  {
    std::cout << "Sending " << x << ", " << y << ", " << rad << std::endl;
    planet(x,y,rad,owner);
  }
  planet(-1,-1,-1, -1);
}

void Server::planet(int x, int y, int rad, int owner)
{
  sf::Packet planet_to_send;
  for (int i = 0; i < client_list.size(); ++i)
  {
    planet_to_send << x << y << rad << owner;
    client_list[i]->Send(planet_to_send);
    planet_to_send.Clear();
  }
}
