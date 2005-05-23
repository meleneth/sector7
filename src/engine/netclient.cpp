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
#include"globals.hpp"
#include"entity.hpp"
#include"sector.hpp"
#include "w_plasmacannon.hpp"
#include<sstream>

extern Console *console;


// Public data members go here.
NetClient::NetClient(std::string servername, int port, std::string nickname) // Constructor
{
    talker = new UDPSocket();
    talker->connect_for_send(servername, port);
    send_hello(talker, nickname);
    listener = talker;
    this->nickname = nickname;
    sector = NULL;
}
    
NetClient::~NetClient() // Destructor
{
    if(talker == listener) talker = NULL;
    if(talker)             delete talker;
    if(listener)           delete listener;
}

extern Entity *my_ship;

Sector *NetClient::do_frame()
{
    Entity *ent;
    Uint32 ent_id;
    Sector *new_sector = NULL;

    if(sector){
        sector->frameupdate();
    }
    NetPacket *packet = NULL;

    while(packet = listener->get_next_packet())
    {
        std::stringstream buf;

        switch(packet->get_command())
        {
            case HELLO:
                console->log("Client got HELLO");
                console->log(packet->command.chatmsg.message);
                sector = new Sector(packet->command.chatmsg.message);
                console->log("sending net full ent req");
                send_net_cmd(talker, REQ_ENT_FULL_UPDATE, 0, NULL);
                sector->dump_all();
                new_sector = sector;
                break;
            case INFO_ENT_FULL:
                EntFull *entdata;
                entdata = (EntFull *) &packet->command;
                ent_id = ntohl(entdata->entID);
                ent =  sector->ent_for_id(ent_id);
                ent->inflateFull(entdata);
                break;
            case INFO_ENT_LOC:
                EntLoc *entLocData;
                entLocData = (EntLoc *) &packet->command;
                ent_id = ntohl(entLocData->entID);
                ent =  sector->ent_for_id(ent_id);
                ent->inflateLoc(entLocData);
                break;
            case ENT_DEATH:
                console->log("client received ent_death\n");
                EntLoc *entData;
                entData = (EntLoc *) &packet->command;
                ent_id = ntohl(entData->entID);
                console->log(buf.str());
                ent = sector->find_ent_for_id(ent_id);
                if(!ent) break;
                buf << "Entity " << ent_id << " at " << ent << " is going to DIE!!";
                console->log(buf.str());
                buf.str("");
                if(ent == my_ship)
                        my_ship = NULL;

                ent->kill_me_now();
                break;
            case CHATMSG:
//                buf << "<client> Recieved: [" << packet->command.chatmsg.message << "] on port " << packet->their_addr.sin_port 
//                    << " from " << inet_ntoa(packet->their_addr.sin_addr);
//                console->log(buf.str());
                console->log(packet->command.chatmsg.message);
                console->render();

                break;
            case GRANT_ENT_WRITE:
                console->log("Giggle on Grant");
                sector->dump_all();
                my_ship = sector->ent_for_id((ENTID_TYPE)ntohl(*(ENTID_TYPE *)packet->command.datamsg.message));
                buf << "Client got GRANT_ENT_WRITE for id " << my_ship->ent_id;
                my_ship->primary = new PlasmaCannon(my_ship);
                console->log(buf.str());
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
    return new_sector;
}

void NetClient::send_line(std::string line)
{
    std::stringstream buf;
    buf << nickname << ": " << line;
    send_chat_message(talker, buf.str());
}

// Private members go here.
// Protected members go here.
