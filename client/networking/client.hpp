#ifndef NETWORKING_H
#define NETWORKING_H
#include <iostream>
#include <string>
#include <cstring>
#include "../game/fleet.hpp"
#include <SFML/Network.hpp>

class Client
{
  std::string error;
  unsigned short port;

  sf::TcpSocket client;
  sf::IpAddress server_ip;
 
  public:

    /**
     * @bbrief constructor for client
     *
     * @param server_ip_address the external IP of the server.
     * @param server_port the port that the server is listening on.
     */
    Client(const char *server_ip_address, unsigned short server_port);

    /**
     * @brief initialise and do everything
     *
     * @return player identifier number
     */
    int join();

    /**
     *
     */
    bool receive_fleet();
    
    /**
     * @brief send new fleet creation to server
     *
     * @param fleet_to_send A pointer to the fleet that needs to be sent to the server
     */
    bool send_fleet(Fleet *fleet_to_send);
};
#endif
