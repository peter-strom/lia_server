
#include "config.hpp"
#include "globals.hpp"

Server server;
Clients clients;
int main(int argc, char *argv[])
{

#ifdef DEBUG_MSG_ON
  std::cout << "Server starting, debugging messages on" << std::endl;
#else
  std::cout << "Server starting, debugging messages off" << std::endl;
#endif
  int port = 555;
  // portnumber
  if (argc != 2)
  {
    std::cerr << "Using default port" << port << std::endl;
  }
  else
  {
    port = atoi(argv[1]);
  }
  server.init(port);
  server.set_connect_cb(&connect_callback);
  server.set_disconnect_cb(&disconnect_callback);
  server.set_receive_cb(&receive_callback);

  while (1)
  {
    server.event_handle();
    usleep(2000*1000);
    std::cout << "hej" << std::endl;
      server.transmit(4, (char*)"password", 9);
  }

  return 0;
}