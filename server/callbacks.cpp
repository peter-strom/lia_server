#include "callbacks.hpp"
#include "../globals.hpp"
#include "../protobuf/measure.pb.h"

using namespace std;

void connect_callback(uint16_t fd)
{
  cout << "[connect callback]" << endl;
  Client client;

  clients.add_client(fd);
  if (clients.get_client(fd, &client))
  {
    cout << "client found in list " << fd << endl;
    client.set_auth(false);

    if (client.get_auth())
    {
      cout << "client authorized" << endl;
    }
    else
    {
      cout << "client not authorized" << endl;
      char msg[] = "password";
      server.transmit(fd, msg, 14);
    }
  }
  else
  {
    cout << "client not found in list " << endl;
  }
}

void receive_callback(uint16_t fd, char *buffer, size_t size)
{
  
  cout << "[receive callback] msg received from socket_fd: " << fd << endl;
#ifdef DEBUG_MSG_ON
  //cout << "Message size: " << size << " bytes." << endl;
  //cout << "Message in hex: "<< hex << buffer << endl;
 // for(uint8_t i = 0; i< size; i++)
 // {
    //cout << "Message in hex: "<< hex << (int8_t)buffer[i] << endl;
  //  printf("%2x ",(uint8_t)buffer[i]);
 // }
  
#endif
if(buffer[0] == 0x08 && buffer[1] == 0x19)
{
  measure::MeasureMsg msg;
  msg.ParseFromString(buffer);
  cout << "size: " << dec << msg.size() << endl;
  cout << "temp: " << msg.temperature() << endl;
  cout << "humidity: " <<msg.humidity() << endl;
  cout << "time: " << msg.timestamp() << endl; 
  cout << "hexdump:" << endl;
  for(uint8_t i = 0; i< msg.size(); i++)
  {
    //cout << "Message in hex: "<< hex << (int8_t)buffer[i] << endl;
    printf("%2x ",(uint8_t)buffer[i]);
  }
  printf("\r\n");
}
  Client client;
  if (clients.get_client(fd, &client))
  {
    //cout << "client found in list " << endl;

    if (client.get_auth())
    {
      cout << "client authorized" << endl;

      if (size < 10)
      {
        //cout << " msg: " << buffer << endl;
      }
    }
    else
    {
      //cout << "client not authorized" << endl;
      if (strcmp(buffer, "PRODUCT_Nsecret handshake") == 0)
      {
        cout << "client autorized!" << fd << endl;
        client.set_auth(true);
      }
    }
  }
  else
  {
    cout << "client not found in list " << endl;
  }

   //cout << "size: " << size <<  " message: \"" << buffer << "\" from client: " << fd << endl;
}

void disconnect_callback(uint16_t fd)
{
  cout << "[disconnect callback] client: " << fd << endl;
}
