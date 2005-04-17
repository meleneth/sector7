#include "netserver.hpp"
/*
** Listener.c -- a datagram sockets "server" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 4950    // the port users will be connecting to

#define MAXBUFLEN 100

//#include"ncu.hpp"

// Public data members go here.
NetServer::NetServer(int port) // Constructor
{
    console->log("Starting net server..");
    listener = new UDPSocket();
    listener->setup_for_listen(port);
}
    
NetServer::~NetServer() // Destructor
{
    std::list<UDPSocket *>::iterator i;

    for(i = clients.begin() ; i!=clients.end(); i++)
    {
        delete *i;
    }
    delete listener;
}

void NetServer::handle_packet(NetPacket *packet)
{
    UDPSocket *replysock;
    NetPacket *replypacket;

    std::stringstream buf;
        switch(packet->get_command())
        {
            case HELLO:
                buf << packet->command.hello.nickname << " connected.";
                console->log(buf.str());
                send_hello(add_client_socket(&packet->their_addr), "HIYA");
                break;
            case CHATMSG:
                buf << "<server> Recieved: [" << packet->command.chatmsg.message << "] on port " << packet->their_addr.sin_port 
                    << " from " << inet_ntoa(packet->their_addr.sin_addr);
//                console->log(buf.str());
                console->render();
                send_all_clients(packet->data_length, packet->command.buf);
                break;
            case GOODBYE:
                console->log("Server got GOODBYE");
                break;
            default:
                console->log("Server got unknown msg!");
            break;
        }
}

void NetServer::do_frame(void)
{
    NetPacket *packet = listener->get_next_packet();
    if(packet){
        handle_packet(packet);
        delete packet;
    }

    std::list<UDPSocket *>::iterator i;

    for(i = clients.begin() ; i!=clients.end(); i++)
    {
        packet = (*i)->get_next_packet();
        if(packet){
            handle_packet(packet);
            delete packet;
        }
    }


}

void NetServer::send_all_clients(int length, void *data)
{
    std::list<UDPSocket *>::iterator i;

    for(i = clients.begin() ; i!=clients.end(); i++)
    {
        (*i)->send(length, data);
    }
}

UDPSocket *NetServer::add_client_socket(struct sockaddr_in *sock)
{
    UDPSocket *reply = new UDPSocket();
    reply->setup_reply_socket(sock);
    clients.push_front(reply);
    return reply;
}

// Private members go here.
// Protected members go here.
