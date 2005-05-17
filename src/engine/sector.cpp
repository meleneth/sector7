#include "sector.hpp"
#include "globals.hpp"
#include "asteroid.hpp"
#include "entity.hpp"
#include "netpacket.hpp"
#include "netserver.hpp"
#include "udpsocket.hpp"
#include "area.hpp"

extern NetServer *server;

#define SECTOR_SIDE 90000

// Public data members go here.
Sector::Sector(std::string sector_id) // Constructor
{
    this->sector_id = sector_id;
    is_master = 0;
    console->log("Sector " + sector_id + " created");
    position = new Vector();
    bound = new Area(SECTOR_SIDE, SECTOR_SIDE);
}
    
Sector::~Sector() // Destructor
{
}

void Sector::setup_master(void)
{
    is_master = 1;
    add_entity(new Asteroid(64));
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
    ship->v->x = 20;
    ship->v->y = 20;
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
    std::list < Sector * >::iterator s;

    if(server){
        NetPacket *data = new NetPacket(sizeof(EntFull));
        EntFull *entData = (EntFull *) &data->command;
        entity->deflateFull(entData);
        entData->cmd = (NetCmd) htonl(INFO_ENT_FULL);
        server->send_all_clients(data);
    }

    entity->sector = this;
    visible_entities.push_front(entity); 
    for (s = attached_sectors.begin(); s != attached_sectors.end(); s++) {
        (*s)->visible_entities.push_front(entity);
    }
    return EntityMgr::add_entity(entity);
} 

void Sector::attach_sector(Sector *sector)
{
    std::list < Sector * >::iterator s;
    std::list < Entity * >::iterator e;

    for (e = sector->entities.begin(); e != sector->entities.end(); e++) {
	    visible_entities.push_front(*e);
        for (s = attached_sectors.begin(); s != attached_sectors.end(); s++) {
            (*s)->visible_entities.push_front(*e);
        }
    }

    for (e = entities.begin(); e != entities.end(); e++) {
        sector->visible_entities.push_front(*e);
    }

    attached_sectors.push_front(sector);
    sector->attached_sectors.push_front(this);
}

void Sector::detach_sector(Sector *sector)
{
    std::list < Sector * >::iterator s;
    std::list < Entity * >::iterator e;

    attached_sectors.remove(sector);
    
    for (e = entities.begin(); e != entities.end(); e++) {
        sector->visible_entities.remove(*e);
    }

    for (e = sector->entities.begin(); e != sector->entities.end(); e++) {
	    visible_entities.remove(*e);
        for (s = attached_sectors.begin(); s != attached_sectors.end(); s++) {
            (*s)->visible_entities.remove(*e);
        }
    }

}

void Sector::render(void)
{
    std::list < Entity * >::iterator i;
    num_ents = 0;

    glColor4f (1, 1, 1, 1);

    for (i = visible_entities.begin (); i != visible_entities.end (); ++i)
    {
          (*i)->render();
          num_ents++;
    }
}

void Sector::remove_ent(Entity *entity)
{
    visible_entities.remove(entity);
    EntityMgr::remove_ent(entity);
}

// Private members go here.
// Protected members go here.
