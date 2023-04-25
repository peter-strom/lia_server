
#include "config.hpp"
#include "server/server.hpp"
#include "callbacks/callbacks.hpp"
// Server side
int main(int argc, char *argv[])
{

#ifdef DEBUG_MSG_ON
  std::cout << "Server starting, debugging messages on" << std::endl;
#else
  std::cout << "Server starting, debugging messages off" << std::endl;
#endif

  // portnumber
  if (argc != 2)
  {
    std::cerr << "Usage: port" << std::endl;
    exit(0);
  }
  int port = atoi(argv[1]);

  Server server(port);
  server.set_connect_cb(&connect_callback);
  server.set_disconnect_cb(&disconnect_callback);
  server.set_receive_cb(&receive_callback);

  while (1)
  {
    server.event_handle();
  }

  return 0;
}