#include "netclient.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include"console.hpp"

extern Console *console;

#define MYPORT 4950    // the port users will be connecting to

// Public data members go here.
NetClient::NetClient(std::string servername, int port, std::string nickname) // Constructor
{
    talker = new UDPSocket();
    talker->connect_for_send(servername, port);
    send_hello(talker, nickname);
    listener = talker;
    this->nickname = nickname;
}
    
NetClient::~NetClient() // Destructor
{
    if(talker == listener)
        talker = NULL;
    if(talker)
        delete talker;
    if(listener)
        delete listener;
}

void NetClient::do_frame(void)
{
    NetPacket *packet = listener->get_next_packet();
    if(packet)
    {
        std::stringstream buf;

        switch(packet->get_command())
        {
            case HELLO:
                console->log("Client got HELLO");
                talker = new UDPSocket();
                talker->setup_reply_socket(&packet->their_addr);
                break;
            case CHATMSG:
                buf << "<client> Recieved: [" << packet->command.chatmsg.message << "] on port " << packet->their_addr.sin_port 
                    << " from " << inet_ntoa(packet->their_addr.sin_addr);
//                console->log(buf.str());
                console->log(packet->command.chatmsg.message);
                console->render();

                break;
            case GOODBYE:
                console->log("Client got GOODBYE");
                break;
            default:
                console->log("Client got unknown msg!");
            break;
        }

        delete packet;
    }

}

void NetClient::send_line(std::string line)
{
    std::stringstream buf;
    buf << nickname << ": " << line;
    send_chat_message(talker, buf.str());
}

// Private members go here.
// Protected members go here.
