#ifndef ___netserver_inc
#define ___netserver_inc 1

#include"SDL.h"


#include"udpsocket.hpp"
#include<list>
#include"sector.hpp"

class NetServer {
    public:
        // Public data members go here.
        NetServer::NetServer(int bar); // Constructor
        NetServer::~NetServer(); // Destructor
        void send_all_clients(int length, void *data);
        UDPSocket *add_client_socket(struct sockaddr_in *sock); // Adds new client to the list, and returns it
        void do_frame(void);
        void handle_packet(NetPacket *packet);
        
        UDPSocket *listener;
        std::list<UDPSocket *> clients;
        Sector *sector;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
