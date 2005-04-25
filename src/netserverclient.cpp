#include "netserverclient.hpp"

// Public data members go here.
NetServerClient::NetServerClient(UDPSocket * clientSocket) // Constructor
{
    socket = clientSocket;
    this->entity = NULL;
}
    
NetServerClient::~NetServerClient() // Destructor
{
}

int NetServerClient::Foo(void)
{
}

// Private members go here.
// Protected members go here.
