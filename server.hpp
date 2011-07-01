#include <SFML/Network.hpp>

class Server
{

  int max_clients;
  int clients;
  std::string error;
  unsigned short port;

  sf::TcpListener listener;

  public:

    Server(unsigned short listening_port, int maximum_clients);
    
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
