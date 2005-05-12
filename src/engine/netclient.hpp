#ifndef ___netclient_inc
#define ___netclient_inc 1

#include"SDL.h"

#include<iostream>

#include"udpsocket.hpp"
#include"sector.hpp"
#include"camera.hpp"

class NetClient {
    public:
        // Public data members go here.
        NetClient::NetClient(std::string servername, int port, std::string nickname); // Constructor
        NetClient::~NetClient(); // Destructor
        Sector *do_frame(Camera *camera);
        void send_line(std::string line);

        std::string nickname;

        Sector *sector;
        
        UDPSocket *talker;
        UDPSocket *listener;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
