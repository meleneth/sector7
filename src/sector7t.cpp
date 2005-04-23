#include"assert.h"

#include<string>

#include"console.hpp"
#include"netserver.hpp"
#include"texture.hpp"

Console *console;
NetServer *server;

int test_entity_marshalling(void);

int main(char *argv[], int argc)
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

    ent->v->x = 20;
    ent->v->y = 20;

    ent->size = 48;
    ent->texture = get_tex_id(TILE_SHIP);

    ent->deflateFull(&info);
    ent->inflateFull(&info);

    assert(ent->v->x == 20);
    assert(ent->v->y == 20);

    assert(ent->size == 48);
}
