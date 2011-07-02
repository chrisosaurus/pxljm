#include "client.hpp"

int main()
{
  Client my_client("10.1.1.104", 7000);
  int player_id = my_client.join();
  if (player_id > -1)
  {
    std::cout << "Apparently I am player #" << player_id << std::endl;
  }
}
