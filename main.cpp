
#include "config.hpp"
#include "globals.hpp"
using namespace std;

Server server;
Clients clients;
int main(int argc, char *argv[])
{

#ifdef DEBUG_MSG_ON
  cout << "Server starting, debugging messages on" << endl;
#else
  cout << "Server starting, debugging messages off" << endl;
#endif
  int port = 555;
  // portnumber
  if (argc != 2)
  {
    cerr << "Using default port" << port << endl;
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
    usleep(200*1000);
     
  }

  return 0;
}