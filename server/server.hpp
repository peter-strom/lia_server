#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#define DEFAULT_PORT 555
#define RX_BUFFER_SIZE 100

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include "config.hpp"
/*
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
*/

/**
 * @brief class for server
 *
 */
class Server
{
public:
  Server();
  Server(uint16_t port);
  ~Server();
  void init(uint16_t port);
  void event_handle();
  void set_connect_cb(void (*con_cb)(uint16_t fd));
  void set_receive_cb(void (*rx_cb)(uint16_t fd, char *rxBuff));
  void set_disconnect_cb(void (*discon_cb)(uint16_t fd));
  uint16_t transmit(uint16_t source_fd, char *txBuff);

private:
  int socket_fd;
  int tempSocket_fd;
  sockaddr_in servAddr;
  char rxBuffer[RX_BUFFER_SIZE];

  void (*connect_cb)(uint16_t fd);
  void (*receive_cb)(uint16_t fd, char *buffer);
  void (*disconnect_cb)(uint16_t fd);
}

#endif /* _SERVER_HPP_ */