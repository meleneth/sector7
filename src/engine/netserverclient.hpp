#ifndef ___netserverclient_inc
#define ___netserverclient_inc 1

#include"SDL.h"
#include"udpsocket.hpp"
#include"entity.hpp"

class NetServerClient {
    public:
        // Public data members go here.
        NetServerClient(UDPSocket *clientSocket, Entity *entity); // Constructor
        ~NetServerClient(); // Destructor
        int Foo(void);

        UDPSocket *socket;
        Entity *entity; 
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
