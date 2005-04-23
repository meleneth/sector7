#include"assert.h"

#include<string>

#include"console.hpp"
#include"netserver.hpp"
#include"texture.hpp"

Console *console;
NetServer *server;

int test_entity_marshalling(void);

int main(int argc, char *argv[])
{
    console = new Console();
    console->print_logs = 1;

    load_textures(1);

    std::string foo;
    foo = "Bar";
    assert(foo.length() ==3);

    printf ("Testing entity marshalling\n");
    test_entity_marshalling();

}

int test_entity_marshalling(void)
{
    Entity *ent = new Entity();
    EntFull info;

    Sint32 foo = -50;

    foo = ntohl(htonl(foo));

    std::stringstream buf;
    buf << "TILE_SHIP is " << (int) TILE_SHIP << " and TILE_NOTILE is " << (int) TILE_NOTILE;
    console->log(buf.str());

    assert(foo == -50);
    
    ent->v->x = -20;
    ent->v->y = 20;

    ent->size = 48;
    ent->texture = get_tex_id(TILE_SHIP);

    ent->deflateFull(&info);

    console->log("Calling new Entity()");
    ent = new Entity();
    console->log("Calling inflateFull()");
    ent->inflateFull(&info);

    assert(ent->v->x == -20);
    assert(ent->v->y == 20);

    assert(ent->size == 48);
    assert(ent->texture == get_tex_id(TILE_SHIP));
}
