#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "../config.hpp"

/**
 * @brief class for client
 *
 */
class Client
{
public:
  Client();
  Client(uint16_t fd);
  ~Client();
  bool get_auth();
  void set_auth(bool value);

private:
  uint16_t clientSocket_fd;
  bool auth;

  void init(uint16_t fd);
  
};

#endif /* _CLEINT_HPP_ */