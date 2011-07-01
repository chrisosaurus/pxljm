#include "client.hpp"

Client::Client(const char *server_ip_address, unsigned short server_port)
  : server_ip(server_ip_address),
  port(server_port)
{
}

Client::get_error()
{
  return error;
}

Client::init()
{
  if (client.Connect(server_ip, port) != sf::Socket::Done)
  {
    std::cout << "Could not connect to server at " << server_ip << ":" << port << std::endl;
    error = "Could not connect to server at " << server_ip << ":" << port;
    return false;
  }
}
