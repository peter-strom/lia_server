#include "server.hpp"
using namespace std;

Server::Server()
{
}

Server::~Server()
{
#ifdef DEBUG_MSG_ON
  cout << "Server destructor" << endl;
#endif
  close(socket_fd);
}

/**
 * @brief initiate socket server
 * @details
 * AF_INET = IPv4
 * SOCK_STREAM = TCP
 *
 * @param[in] port the desired portnumer the server listens to
 */
void Server::init(uint16_t port)
{
  bzero((char *)&servAddr, sizeof(servAddr));
  bzero(rxBuffer, RX_BUFFER_SIZE);
  FD_ZERO(&socket_fds);
  FD_ZERO(&tempSocket_fds);

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(port);

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0)
  {
#ifdef DEBUG_MSG_ON
    cerr << "Error [init] socket creation failed" << endl;
#endif
    exit(0);
  }
#ifdef DEBUG_MSG_ON
  cout << "socket() file descriptor: " << socket_fd << endl;
#endif

  // server restart fix
  int enable = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
  {
#ifdef DEBUG_MSG_ON
    cerr << "Error [init] SO_REUSADDR" << endl;
#endif
  }

  // bind

  if (bind(socket_fd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
  {
#ifdef DEBUG_MSG_ON
    cerr << "Error [init] binding socket to local address : " << errno << endl;
#endif
    exit(0);
  }

  FD_SET(socket_fd, &socket_fds);
  maxFd_u16 = socket_fd;

  // listen for up to 5 requests at a time
  if (listen(socket_fd, 5) < 0)
  {
#ifdef DEBUG_MSG_ON
    cerr << "Error [init] init listen failed : " << endl;
#endif
    exit(0);
  }
#ifdef DEBUG_MSG_ON
  cout << "init done: Waiting for a client to connect..." << endl;
#endif
}

void Server::event_handle()
{
  tempSocket_fds = socket_fds;
  timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 100000;

  if (select(maxFd_u16 + 1, &tempSocket_fds, NULL, NULL, &timeout) < 0)
  {
#ifdef DEBUG_MSG_ON
    cerr << "Error [event_handle] select failed" << endl;
#endif
    exit(0);
  }

  for (uint16_t i = 0; i <= maxFd_u16; i++)
  {
    if (FD_ISSET(i, &tempSocket_fds))
    {
      if (socket_fd == i)
      {
        handle_new_connection();
      }
      else
      {
        handle_existing_connection(i);
      }
    }
  }
}

void Server::handle_new_connection()
{
#ifdef DEBUG_MSG_ON
  cout << "new connection socket_fd: " << socket_fd << endl;
#endif
  socklen_t addrLen = sizeof(clientAddr_storage);
  tempSocket_fd = accept(socket_fd, (sockaddr *)&clientAddr_storage, &addrLen);

  if (tempSocket_fd < 0)
  {
#ifdef DEBUG_MSG_ON
    cerr << "Error [handle_new_connection] accept failed" << endl;
#endif
    exit(0);
  }
  else
  {
    FD_SET(tempSocket_fd, &socket_fds);
    if (tempSocket_fd > maxFd_u16)
    {
      maxFd_u16 = tempSocket_fd;
    }
    // inet_ntop(clientAddr_storage.ss_family, get_in_addr((sockaddr*)&clientAddr_storage), ...
  }
  connect_cb(tempSocket_fd);
}

void Server::handle_existing_connection(int fd)
{
  int rxBytes = recv(fd, rxBuffer, RX_BUFFER_SIZE, 0);

  if (rxBytes <= 0)
  {
    if (rxBytes < 0) // fail
    {
#ifdef DEBUG_MSG_ON
      cerr << "Error [handle_existing_connection] recv failed" << endl;
#endif
    }
    else
    {
      disconnect_cb(fd);
    }

    close(fd);
    FD_CLR(fd, &socket_fds);
  }
  else
  {
    receive_cb(fd, rxBuffer, sizeof(rxBuffer));
    bzero(rxBuffer, RX_BUFFER_SIZE);
  }
}

void Server::set_connect_cb(void (*con_cb)(uint16_t fd))
{
  connect_cb = con_cb;
}

void Server::set_receive_cb(void (*rx_cb)(uint16_t fd, char *rxBuff, size_t size))
{
  receive_cb = rx_cb;
}

void Server::set_disconnect_cb(void (*discon_cb)(uint16_t fd))
{
  disconnect_cb = discon_cb;
}

uint16_t Server::transmit(uint16_t source_fd, char *txBuff, size_t size)
{
  return send(source_fd, txBuff, size, 0);
}