#include <iostream>
#include <string>
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
    bool receive_action();

    bool send_action();
};
