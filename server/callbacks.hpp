#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

#include "../config.hpp"

void connect_callback(uint16_t fd);
void receive_callback(uint16_t fd, char *buffer, size_t size);
void disconnect_callback(uint16_t fd);

#endif /* _CALLBACKS_HPP_ */