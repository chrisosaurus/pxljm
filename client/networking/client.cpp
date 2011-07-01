#include "client.hpp"

Client::Client(const char *server_ip_address, unsigned short server_port)
  : server_ip(server_ip_address),
  port(server_port)
{
}

std::string Client::get_error()
{
  return error;
}

bool Client::init()
{
  if (client.Connect(server_ip, port) != sf::Socket::Done)
  {
    error = "Could not connect to server.";
    return false;
  }
}
