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

void send_net_cmd(UDPSocket *socket, NetCmd command, Uint32 length, const void *data)
{
    NetPacket *packet = new NetPacket(length + sizeof(NetCmd));
    packet->set_command(command);
    memcpy(&packet->command.datamsg.message, data, length);
    socket->send(packet);
    delete packet;
}

void send_chat_message(UDPSocket *socket, std::string line)
{
    send_net_cmd(socket, CHATMSG, line.length(), line.c_str());
}

void send_hello(UDPSocket *socket, std::string nickname)
{
    send_net_cmd(socket, HELLO, nickname.length()+1, nickname.c_str()); 
}

void send_goodbye(UDPSocket *socket, std::string quitmsg)
{
    send_net_cmd(socket, GOODBYE, quitmsg.length(), quitmsg.c_str()); 
}



