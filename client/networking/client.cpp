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
  std::cout << "Waiting for ready message" << std::endl;
  sf::Packet ready_message;
  std::string message;
  client.Receive(ready_message);
  if ((ready_message >> message) && (message == "Ready"))
  {
    std::cout << "Received ready message. Sending reply." << std::endl;
  }
  else
  {
    std::cout << "Couldn't extract data. Something's gone wrong. It's best if I close now." << std::endl;
    return false;
  }

  client.Send("Ready", 6);
}

bool send_fleet(Fleet *fleet_to_send)
{
  // TODO: send the fleet to server
}
