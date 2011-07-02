#ifndef NETWORKING_H
#define NETWORKING_H
#include <iostream>
#include <string>
#include <cstring>
#include "../game/fleet.hpp"
#include "../game/mothership.hpp"
#include <SFML/Network.hpp>

class ClientGame;

class NetworkingClient
{
  std::string error;
  unsigned short port;

  ClientGame *game;

  sf::TcpSocket client;
  sf::IpAddress server_ip;
 
  public:

    /**
     * @bbrief constructor for client
     *
     * @param server_ip_address the external IP of the server.
     * @param server_port the port that the server is listening on.
     * @param client_game a pointer to ClientGame, so we can add planets when received from the server
     */
    NetworkingClient(const char *server_ip_address, unsigned short server_port);

    void init(ClientGame *client_game);

    /**
     * @brief initialise and do everything
     */
    void join();
    
    /**
     *
     */
    bool receive_packet();
    
    /**
     * @brief send new fleet creation to server
     *
     * @param fleet_to_send A pointer to the fleet that needs to be sent to the server
     */
    bool send_fleet(Fleet *fleet_to_send);

    bool send_moship(int moship_id, int timestamp, int x_dest, int y_dest);
};
#endif
