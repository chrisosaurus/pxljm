#include <string>
#include <list>
#include <iostream>
#include <SFML/Network.hpp>

class Server
{
  int clients;
  std::string error;
  unsigned short port;

  sf::TcpListener listener;
  sf::SocketSelector selector;
  std::list<sf::TcpSocket*> client_list;

  public:
    Server(unsigned short listening_port, int num_clients);
    
    /**
     *
     */
    std::string get_error();

    /**
     * @brief initialise networking stuff
     * @return Returns true if everything went well
     */
    bool init();

    /**
     * @brief receive action over the interwebs or network tubes
     * @return Returns true if everything went well
     */
    bool receive_action();

    /**
     * @brief send action over the interwebs or network tubes
     * @return Returns true if everything went well
    */
    bool send_action();
};
