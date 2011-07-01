#include "client.hpp"

int main()
{
  Client my_client("127.0.0.1", 7000);
  if (!my_client.init())
  {
    std::cout << my_client.get_error() << std::endl;
  }
}
