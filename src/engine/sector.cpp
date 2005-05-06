#include "sector.hpp"
#include "globals.hpp"
#include "entity.hpp"
#include "netpacket.hpp"
#include "netserver.hpp"
#include "udpsocket.hpp"
#include "area.hpp"

extern NetServer *server;

#define SECTOR_SIDE 9000

// Public data members go here.
Sector::Sector(std::string sector_id) // Constructor
{
    this->sector_id = sector_id;
    is_master = 0;
    console->log("Sector " + sector_id + " created");
    position = new Vector();

    s_nw = NULL;
    s_ne = NULL;
    s_sw = NULL;
    s_se = NULL;
    bound = new Area(SECTOR_SIDE, SECTOR_SIDE);
}
    
Sector::~Sector() // Destructor
{
}

void Sector::setup_master(void)
{
    is_master = 1;
    console->log("Master sector initialized.");
}

void Sector::update_visible(void)
{
    visible_entities = entities;

    //if(s_nw)
    //    visible_entities.append(s_nw->entities);
}

Entity *Sector::setup_connecting(void)
{
    Entity *ship;

    ship = new Entity();
    ship->v->set_from_screen_coords(320, 200, 640, 480);
    ship->size = 128;
    ship->texture = get_tex_id(TILE_SHIP);
	ship->sector = this;
    ship->ent_id = 31337;
    add_entity(ship);
}

void Sector::dump(NetPacket *packet)
{
    if(!server){
        return;
    }

    NetServerClient *client = server->get_client(packet);

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


Entity *Sector::add_entity (Entity *entity)
{
    NetPacket *data = new NetPacket(sizeof(EntFull));
    EntFull *entData = (EntFull *) &data->command;

    if(server){
        entity->deflateFull(entData);
        entData->cmd = (NetCmd) htonl(INFO_ENT_FULL);
        server->send_all_clients(data);
    }
    
    entity->sector = this;
    return EntityMgr::add_entity(entity);
} 

// Private members go here.
// Protected members go here.
