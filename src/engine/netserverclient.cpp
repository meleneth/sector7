#include "netserverclient.hpp"

// Public data members go here.
NetServerClient::NetServerClient(UDPSocket * clientSocket, Entity *entity) // Constructor
{
    socket = clientSocket;
    this->entity = entity;
}
    
NetServerClient::~NetServerClient() // Destructor
{
}

int NetServerClient::Foo(void)
{
}

// Private members go here.
// Protected members go here.
