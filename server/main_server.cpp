#include "server.hpp"

int main()
{
  Server my_server(7000, 2);
  if (!my_server.run())
  {
    std::cout << my_server.get_error() << std::endl;
  }
}
