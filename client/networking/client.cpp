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
  char ready_message[8];
  std::size_t received = 0;
  client.Receive(ready_message, sizeof(ready_message), received);
  if (!strcmp(ready_message, "Ready"))
  {
    std::cout << "Received ready message. Sending reply." << std::endl;
  }

  client.Send("Ready", 6);
}

bool send_fleet(Fleet *fleet_to_send)
{
  // TODO: send the fleet to server
}
