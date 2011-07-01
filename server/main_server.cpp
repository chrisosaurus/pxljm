#include "server.hpp"

int main()
{
  Server my_server(55001, 1);
  if (!my_server.init())
  {
    std::cout << my_server.get_error() << std::endl;
  }
}
