#ifndef ___udpsocket_inc
#define ___udpsocket_inc 1

#include"SDL.h"

#include"netpacket.hpp"
#include<list>
#include<iostream>

class UDPSocket {
    public:
        // Public data members go here.
        UDPSocket(); // Constructor
        
        ~UDPSocket(); // Destructor

        NetPacket *get_next_packet(void);

        void setup_for_listen(int port);
        void connect_for_send(std::string hostname, int port);
        void setup_reply_socket(struct sockaddr_in *socket);
        void send(int length, const void *data);
        void send(NetPacket *packet);
        void setup_socket(int port);
        int is_reply_to(struct sockaddr_in *addr);
        int sockfd;
        struct sockaddr_in my_addr;    // my address information
        struct sockaddr_in their_addr; // connector's address information
        int addr_len, numbytes;
        char buf[MAX_NET_BUFFER_LENGTH];
        std::list<NetPacket *> queued_packets;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
