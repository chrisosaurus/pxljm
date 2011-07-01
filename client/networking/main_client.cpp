#include "client.hpp"

int main()
{
  Client my_client("10.1.1.104", 7000);
  if (!my_client.init())
  {
    std::cout << my_client.get_error() << std::endl;
  }
}
