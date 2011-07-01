#include "server.hpp"

Server::Server(unsigned short listening_port, int num_clients)
  : port(listening_port),
  clients(num_clients)
{
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
  ready_message << message;
  for (int i = 0; i < client_list.size(); ++i)
  {
    client_list[i]->Send(ready_message);
  }
  ready_message.Clear();

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
            std::cout << "Client " << i << " is ready" << std::endl;
            ++ready;
          }
        }
      }
    }
  }

  // TODO: Send planets


  // Main loop yay
  while (true)
  {
    if (selector.Wait())
    {
      for (int i = 0; i < client_list.size(); ++i)
      {
        sf::TcpSocket *client_sending = client_list[i];
        if (selector.IsReady(*client_sending))
        {
          //receive fleet
        }
        for (int j = 0; j < client_list.size(); ++j)
        {
          if (client_list[j] == client_sending)
          {
            continue;
          }
          //send fleet
        }
      }
    }
  }
}
