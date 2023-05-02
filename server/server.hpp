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
#include "../config.hpp"

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
  ~Server();
  void init(uint16_t port);
  void event_handle();
  void set_connect_cb(void (*con_cb)(uint16_t fd));
  void set_receive_cb(void (*rx_cb)(uint16_t fd, char *rxBuff));
  void set_disconnect_cb(void (*discon_cb)(uint16_t fd));
  uint16_t transmit(uint16_t source_fd, char *txBuff, size_t size);

private:
  int socket_fd;
  int tempSocket_fd;
  fd_set socket_fds;
  fd_set tempSocket_fds;
  uint16_t maxFd_u16;

  sockaddr_in servAddr;
  sockaddr_storage clientAddr_storage;
  char rxBuffer[RX_BUFFER_SIZE];

  void handle_new_connection();
  void handle_existing_connection(int socket_fd);

  void (*connect_cb)(uint16_t fd);
  void (*receive_cb)(uint16_t fd, char *buffer);
  void (*disconnect_cb)(uint16_t fd);
};

#endif /* _SERVER_HPP_ */