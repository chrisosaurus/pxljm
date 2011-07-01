#include <iostream>
#include <string>
#include "../game/fleet.hpp"
#include <SFML/Network.hpp>

class Client
{
  std::string error;
  unsigned short port;

  sf::TcpSocket client;
  sf::IpAddress server_ip;
 
  public:
    Client(const char *server_ip_address, unsigned short server_port);
    
    /**
     * @brief get error message
     */
    std::string get_error();

    /**
     * @brief initialise and do everything
     */
    bool init();

    /**
     *
     */
    bool receive_action(Fleet *fleet_received);
    
    /**
     * @brief send new fleet creation to server
     */
    bool send_fleet(Fleet *fleet_to_send);
};
