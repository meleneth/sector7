#include "sector.hpp"
#include "globals.hpp"
#include "entity.hpp"
#include "netpacket.hpp"
#include "netserver.hpp"
#include "udpsocket.hpp"

extern NetServer *server;

// Public data members go here.
Sector::Sector(std::string sector_id) // Constructor
{
    this->sector_id = sector_id;
    is_master = 0;
    console->log("Sector " + sector_id + " created");
}
    
Sector::~Sector() // Destructor
{
}

void Sector::setup_master(void)
{
    is_master = 1;
    console->log("Master sector initialized.");

    Entity *ship;

    ship = new Entity();
    ship->v->set_from_screen_coords(300, 200);
    ship->size = 32;
    ship->texture = get_tex_id(TILE_SHIP);
	ship->sector = this;
    add_entity(ship);
    ship->log_info();
	
    ship = new Entity();
    ship->v->set_from_screen_coords(620, 180);
    ship->size = 32;
    ship->texture = get_tex_id(TILE_SHIP);
	ship->sector = this;
    add_entity(ship);
    ship->log_info();
}

void Sector::setup_connecting(void)
{
    Entity *ship;

    ship = new Entity();
    ship->v->set_from_screen_coords(320, 200);
    ship->size = 128;
    ship->texture = get_tex_id(TILE_SHIP);
	ship->sector = this;
    ship->ent_id = 31337;
    add_entity(ship);
}

void Sector::dump(NetPacket *packet)
{
    NetServerClient *client = get_client(packet);

    NetPacket *dumper = new NetPacket(sizeof(EntFull));


    EntFull *entData = (EntFull *) &dumper->command;
    entData->cmd = (NetCmd) htonl(INFO_ENT_FULL);
    std::list< Entity * >::iterator i;
    for (i = entities.begin(); i != entities.end(); ++i) {
        (*i)->deflateFull(entData);
        client->socket->send(dumper);
    }    

    delete dumper;
}

NetServerClient *Sector::get_client(NetPacket *packet)
{
    std::list< NetServerClient * >::iterator i;
    for (i = server->clients.begin(); i != server->clients.end(); ++i) {
        if ((*i)->socket->is_reply_to(&packet->their_addr)) {
            return *i;
        }
    }
}

Entity *Sector::add_entity (Entity *entity)
{
    NetPacket *data = new NetPacket(sizeof(EntFull));
    EntFull *entData = (EntFull *) &data->command;

    if(server){
        entity->deflateFull(entData);
        entData->cmd = (NetCmd) htonl(INFO_ENT_FULL);
        server->send_all_clients(data);
    }
    
    entities.push_front (entity);
        
    entity->sector = this;
    return EntityMgr::add_entity(entity);
} 

// Private members go here.
// Protected members go here.
