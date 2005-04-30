#include "udpsocket.hpp"


#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

UDPSocket::UDPSocket() 
{
    //setup_socket(port);

    //struct hostent *he;

    //if ((he=gethostbyname(hostname.c_str())) == NULL) {  // get the host info
    //    perror("gethostbyname");
    //    exit(1);
    //}

    //their_addr.sin_family = AF_INET;     // host byte order
    //their_addr.sin_port = htons(port); // short, network byte order
    //their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    //memset(&(their_addr.sin_zero), '\0', 8); // zero the rest of the struct
}

void UDPSocket::setup_reply_socket(struct sockaddr_in *sock)
{
    // Sets up this socket to reply to one that just recieved a packet

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;     // host byte order
    their_addr.sin_port = sock->sin_port; // short, network byte order
    their_addr.sin_addr = sock->sin_addr;
    memset(&(their_addr.sin_zero), '\0', 8); // zero the rest of the struct
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
}

void UDPSocket::setup_for_listen(int port)
{
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;         // host byte order
    my_addr.sin_port = htons(port);     // short, network byte order
    my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct

    const int on = 1;
    if (setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) != 0); 

    if (bind(sockfd, (struct sockaddr *)&my_addr,
                                          sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
}

void UDPSocket::connect_for_send(std::string hostname, int port)
{
    struct hostent *he;
    if ((he=gethostbyname(hostname.c_str())) == NULL) {  // get the host info
        perror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;     // host byte order
    their_addr.sin_port = htons(port); // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(their_addr.sin_zero), '\0', 8); // zero the rest of the struct
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
}

void UDPSocket::setup_socket(int port)
{
}
    
UDPSocket::~UDPSocket() // Destructor
{
}

NetPacket *UDPSocket::get_next_packet()
{
    static NetPacket *new_packet = NULL;

    if(!new_packet){
        new_packet = new NetPacket(MAX_NET_BUFFER_LENGTH);
        new_packet->data_length = 0;
    }

    new_packet->recv(this);
    if(new_packet->data_length){
        NetPacket *packet = new_packet;
        new_packet = NULL;
        return packet;
    }

    return (NetPacket *)NULL;
}

void UDPSocket::send(int length, const void *data)
{
    sendto(sockfd, data, length, 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
}

void UDPSocket::send(NetPacket *packet)
{
    send(packet->data_length, &packet->command);
}

int UDPSocket::is_reply_to(struct sockaddr_in *addr)
{
    return ((their_addr.sin_port == addr->sin_port)
            &&
            (their_addr.sin_addr.s_addr == addr->sin_addr.s_addr) );
} 

// Private members go here.
// Protected members go here.
