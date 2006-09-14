#ifndef ___netpacket_inc
#define ___netpacket_inc 1

#include"SDL.h"

#define MAX_NET_BUFFER_LENGTH 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include<iostream>

class UDPSocket;

enum NetCmd { HELLO, CHATMSG, GOODBYE, 
            GRANT_ENT_WRITE, 
            INFO_ENT_LOC, INFO_ENT_FULL,
				REQ_ENT_FULL_UPDATE, REQ_ENT_LOC_UPDATE,
                    ENT_FIRE, ENT_DEATH
}; 

struct NetCmd_Hello {
    NetCmd command;
    char nickname[16];
};

struct NetCmd_ChatMsg {
    NetCmd command;
    char message[255];
};

struct NetCmd_DataMsg {
    NetCmd command;
    char message[1024];
};

struct NetCmd_GoodBye {
    NetCmd command;
    char quitmsg[255];
};

union NetCommand { 
    NetCmd command;
    NetCmd_Hello hello;
    NetCmd_DataMsg datamsg;
    NetCmd_ChatMsg chatmsg;
    NetCmd_GoodBye goodbye;
    char buf[MAX_NET_BUFFER_LENGTH];
};

class NetPacket {
    public:
        // Public data members go here.
        NetPacket(int length); // Constructor
        NetPacket(int length, void *data);
        ~NetPacket(); // Destructor
        void recv(UDPSocket *socket);
        void set_command(NetCmd cmd);
        NetCmd get_command(void);
        int buffer_length;
        int data_length;
        struct sockaddr_in their_addr;
        NetCommand command;

    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

void send_chat_message(UDPSocket *socket, std::string line);
void send_hello(UDPSocket *socket, std::string nickname);
void send_goodbye(UDPSocket *socket, std::string quitmsg);
void send_net_cmd(UDPSocket *socket, NetCmd command, Uint32 length, const void *data);
void send_net_cmd_string(UDPSocket *socket, NetCmd command, std::string msg);

#endif
