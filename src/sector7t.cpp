#include"assert.h"

#include<string>

#include"console.hpp"
#include"camera.hpp"
#include"netserver.hpp"
#include"texture.hpp"
#include"area.hpp"

Console *console;
NetServer *server;
Entity *my_ship;

int test_partial_entity_update(void);
int test_entity_marshalling(void);
int test_camera(void);
int test_vector(void);
int test_area(void);

int main(int argc, char *argv[])
{
    console = new Console();
    console->print_logs = 1;

    load_textures(1);
    my_ship = NULL;

    std::string foo;
    foo = "Bar";
    assert(foo.length() ==3);

    printf("Testing partial entity updates\n");
    test_partial_entity_update();
    
    printf ("Testing vector\n");
    test_vector();

    printf ("Testing area\n");
    test_area();

    printf ("Testing camera\n");
    test_camera();

    printf ("Testing entity marshalling\n");
    test_entity_marshalling();

}

int test_partial_entity_update(void)
{
    Entity *ent = new Entity();
    EntLoc info;

    Sint32 foo = -50;

    foo = ntohl(htonl(foo));

    assert(foo == -50);
    
    ent->v->x = -20;
    ent->v->y = 20;
    ent->v->angle = 39;
    ent->v->power = 174;
    ent->v->rotation = -23;
    
    ent->deflateLoc(&info);

    console->log("Calling new Entity()");
    ent = new Entity();
    console->log("Calling inflateFull()");
    ent->inflateLoc(&info);

    assert(ent->v->x == -20);
    assert(ent->v->y == 20);
    assert(ent->v->angle == 39);
    assert(ent->v->power == 174);
    assert(ent->v->rotation == -23);
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

int test_vector(void)
{
    Area *bound = new Area(1024, 768);

    Vector *p = new Vector();

    p->x = 200;
    p->y = 200;

    p->bounds_check(bound);

    assert(p->x == 200);
    assert(p->y == 200);

    p->x = 513;
    p->y = 385;

    p->bounds_check(bound);

    assert(p->x == -512);
    assert(p->y == -384);
}

int test_area(void)
{
    Area *area = new Area(320, 200);
    
    Vector *v = new Vector();
    v->x = 100;
    v->y = -23;

    assert(area->contains(v));

    v->x = 400;
    assert(!area->contains(v));
}

int test_camera(void)
{
    Camera *cam = new Camera("camera1");
    Entity *ent = new Entity();

    ent->v->x = 5000;
    ent->v->y = 5000;

    cam->follow(ent);

    assert(cam->position->x == 4600);
    assert(cam->position->y == 4600);
}
