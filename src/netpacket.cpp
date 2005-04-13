#include "netpacket.hpp"
#include "udpsocket.hpp"

// Public data members go here.
NetPacket::NetPacket(int length) // Constructor
{
    this->buffer_length = length;
    data_length=length;
}

NetPacket::NetPacket(int length, void *data)
{
    this->buffer_length = length;
    data_length=0;
}
    
NetPacket::~NetPacket() // Destructor
{
}

void NetPacket::set_command(NetCmd cmd)
{
    command.command = (NetCmd)htonl(cmd);
}

NetCmd NetPacket::get_command(void)
{
    return (NetCmd) ntohl(command.command);
}

void NetPacket::recv(UDPSocket *socket)
{
    int numbytes;
    int addr_len = sizeof(struct sockaddr);
    if ((numbytes=recvfrom(socket->sockfd,command.buf, MAX_NET_BUFFER_LENGTH-1, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
        if(errno != EAGAIN){
            perror("recvfrom");
            exit(1);
        }
    }else{
        command.buf[numbytes] = '\0';
        data_length = numbytes;
    }
}

// Private members go here.
// Protected members go here.

void send_chat_message(UDPSocket *socket, std::string line)
{
    NetPacket *packet = new NetPacket(line.length() + sizeof(NetCmd));
    packet->set_command(CHATMSG);
    strcpy((char *)&packet->command.chatmsg.message, line.c_str());
    socket->send(packet);
    delete packet;
}

void send_hello(UDPSocket *socket, std::string nickname)
{
    NetPacket *packet = new NetPacket(nickname.length() + sizeof(NetCmd));
    packet->set_command(HELLO);
    strcpy((char *)&packet->command.hello.nickname, nickname.c_str());
    socket->send(packet);
    delete packet;
}

void send_goodbye(UDPSocket *socket, std::string quitmsg)
{
    NetPacket *packet = new NetPacket(quitmsg.length() + sizeof(NetCmd));
    packet->set_command(GOODBYE);
    strcpy((char *)&packet->command.goodbye.quitmsg, quitmsg.c_str());
    socket->send(packet);
    delete packet;
}



