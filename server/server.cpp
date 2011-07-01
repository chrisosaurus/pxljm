#include "server.hpp"

Server::Server(unsigned int listening_port, int num_clients)
  : port(listening_port),
  clients(num_clients)
{
}

Server::get_error()
{
  return error;
}

Server::init()
{
  std::cout << "Trying to listen on port " << port << std::endl;
  if (listener.Listen(port) != sf::Socket::Done)
  {
    std::cout << "Could not create socket" << std::endl;
    error = "Could not create socket";
    return false;
  }
  int clients_so_far;
  std::cout << "Waiting for " << clients << "client(s)" << std::cout;
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
        if (listener.Accpet(*client) == sf::Socket::Done)
        {
          clients_so_far.push_back(client);
          selector.Add(*client);
          ++clients_so_far;
          std::cout << clients_so_far << " have connected so far" << std::endl;
        }
      }
    }
  }
  std::cout << "All clients have connected. Starting game..." << std::endl;
}
