#include "server.hpp"

Server::Server()
{
  init(DEFAULT_PORT);
}

Server::Server(uint16_t port)
{
  init(port);
}

Server::~Server()
{
#ifdef DEBUG_MSG_ON
  std::cout << "Server destructor" << std::endl;
#endif
  close(socket_fd);
}

void Server::init(uint16_t port)
{
  bzero((char *)&servAddr, sizeof(servAddr));
  bzero(rxBuffer,RX_BUFFER_SIZE);

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(port);

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    #ifdef DEBUG_MSG_ON
    std::cout << "Socket creation failed" << std::endl;
    #endif
    exit(0);
  }

  // server restart fix
  int enable = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
  {
    #ifdef DEBUG_MSG_ON
    std::cout << "Error SO_REUSADDR" << std::endl;
    #endif
  }

}

void Server::event_handle()
{
}

void Server::set_connect_cb(void (*con_cb)(uint16_t fd))
{
  Server::connect_cb = con_cb;
}

void Server::set_receive_cb(void (*rx_cb)(uint16_t fd, char *rxBuff))
{
  Server::receive_cb = rx_cb;
}

void Server::set_disconnect_cb(void (*discon_cb)(uint16_t fd))
{
  Server::disconnect_cb = discon_cb;
}

uint16_t Server::transmit(uint16_t source_fd, char *txBuff)
{
  return send(source_fd, txBuff, sizeof(txBuff), 0);
}