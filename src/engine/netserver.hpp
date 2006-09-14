#ifndef ___netserver_inc
#define ___netserver_inc 1

#include"SDL.h"


#include"udpsocket.hpp"
#include<list>
#include"sector.hpp"
#include"netserverclient.hpp"

class NetServer : public Sector {
    public:
        // Public data members go here.
        NetServer(int port, std::string sector_id); // Constructor
        ~NetServer(); // Destructor
        void send_all_clients(int length, void *data);
        void send_all_clients(NetPacket *packet);
        void send_all_clients(NetPacket *packet, NetServerClient *except_me);
        UDPSocket *add_client_socket(struct sockaddr_in *sock); // Adds new client to the list, and returns it
        void do_frame(void);
        void handle_packet(NetPacket *packet);
        NetServerClient *get_client(NetPacket *packet);
        void handle_hello(NetPacket *packet);
        virtual Entity *add_entity(Entity *entity);
        virtual void remove_ent(Entity *entity);
        Entity *new_player_ship(void);
        void dump(NetPacket *packet);

        
        Uint32 ent_id;
        UDPSocket *listener;
        std::list< NetServerClient * > clients;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
