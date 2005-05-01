#include "netserver.hpp"
#include "globals.hpp"
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

#include"console.hpp"
#include"entity.hpp"

extern Console *console;

//#include"ncu.hpp"

#include<sstream>

// Public data members go here.
NetServer::NetServer(int port) // Constructor
{
    console->log("Starting net server..");
    listener = new UDPSocket();
    listener->setup_for_listen(port);
    sector = NULL;
}
    
NetServer::~NetServer() // Destructor
{
    std::list< NetServerClient * >::iterator i;

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
    NetServerClient *client;

    ENTID_TYPE ent_id;
    Entity *ent;

    std::stringstream buf;

        switch(packet->get_command())
        {
            case HELLO:
                console->log("Calling handle_hello");
                handle_hello(packet);
                console->log(" ... And lived through the experience");
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
            case REQ_ENT_FULL_UPDATE:
                console->log("Server got REQ_ENT_FULL_UPDATE");
                sector->dump(packet);
                break;
            case INFO_ENT_FULL:
                EntFull *entdata;
                entdata = (EntFull *) &packet->command;
                ent_id = ntohl(entdata->entID);

                client = get_client(packet);
                ent =  sector->ent_for_id(ent_id);

                if(client->entity->ent_id == ent_id){
                    client->entity->inflateFull(entdata);
                    send_all_clients(packet, client);
                }
                break;
            case REQ_ENT_LOC_UPDATE:
                console->log("Server got REQ_ENT_LOC_UPDATE");
                sector->dump(packet);
                break;
            case INFO_ENT_LOC:
                EntLoc *entLocData;
                entLocData = (EntLoc *) &packet->command;
                ent_id = ntohl(entLocData->entID);

                client = get_client(packet);
                ent =  sector->ent_for_id(ent_id);

                if(client->entity->ent_id == ent_id){
                    client->entity->inflateLoc(entLocData);
                    send_all_clients(packet, client);
                }
                break;
            default:
                console->log("Server got unknown msg!");
            break;
        }
}
   
void NetServer::handle_hello(NetPacket *packet)
{
     std::stringstream buf;

     Entity * newEnt = new Entity();
     newEnt->v->random_location(50, 50, 300, 300);
     newEnt->texture = get_tex_id(TILE_SHIP);
     sector->add_entity(newEnt); 

     buf << packet->command.hello.nickname << " connected.  Directing it to sector: " << sector->sector_id
         << " ent_id: " << newEnt->ent_id;
     console->log(buf.str());

     ENTID_TYPE entid = htonl(newEnt->ent_id);

     NetServerClient *netserverclient = new NetServerClient(add_client_socket(&packet->their_addr), newEnt);
     clients.push_front(netserverclient);
     send_hello(netserverclient->socket, sector->sector_id);
     send_net_cmd(netserverclient->socket, GRANT_ENT_WRITE, sizeof(ENTID_TYPE), &entid);
}

void NetServer::do_frame(void)
{
    NetPacket *packet = listener->get_next_packet();
    if(packet){
        handle_packet(packet);
        delete packet;
    }

    std::list< NetServerClient * >::iterator i;

    for(i = clients.begin() ; i!=clients.end(); i++)
    {
        packet = (*i)->socket->get_next_packet();
        if(packet){
            handle_packet(packet);
            delete packet;
        }
    }


}

void NetServer::send_all_clients(int length, void *data)
{
    std::list< NetServerClient * >::iterator i;

    for(i = clients.begin() ; i!=clients.end(); i++)
    {
        (*i)->socket->send(length, data);
    }
}

void NetServer::send_all_clients(NetPacket *packet)
{
    std::list< NetServerClient * >::iterator i;

    for(i = clients.begin() ; i!=clients.end(); i++)
    {
        (*i)->socket->send(packet);
    }
}

void NetServer::send_all_clients(NetPacket *packet, NetServerClient *except_me)
{
    std::list< NetServerClient * >::iterator i;

    for(i = clients.begin() ; i!=clients.end(); i++)
    {
        if((*i) != except_me){
            (*i)->socket->send(packet);
        }
    }
}

UDPSocket *NetServer::add_client_socket(struct sockaddr_in *sock)
{
    UDPSocket *reply = new UDPSocket();
    reply->setup_reply_socket(sock);
    return reply;
}

NetServerClient *NetServer::get_client(NetPacket *packet)
{
    std::list< NetServerClient * >::iterator i;
    for (i = clients.begin(); i != clients.end(); ++i) {
        if ((*i)->socket->is_reply_to(&packet->their_addr)) {
            return *i;
        }
    }
}


// Private members go here.
// Protected members go here.
