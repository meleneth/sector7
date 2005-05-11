#include"assert.h"

#include<string>

#include"console.hpp"
#include"camera.hpp"
#include"w_plasmacannon.hpp"
#include"netserver.hpp"
#include"texture.hpp"
#include"area.hpp"
#include"SDL.h"

Console *console;
NetServer *server;
Entity *my_ship;

int test_partial_entity_update(void);
int test_entity_marshalling(void);
int test_shooting(void);
int test_camera(void);
int test_vector(void);
int test_area(void);
int test_sdl_delay(void);
int test_collision_detection(void);

int main(int argc, char *argv[])
{
    console = new Console();
    console->print_logs = 1;

    load_textures(1);
    my_ship = NULL;

    std::string foo;
    foo = "Bar";
    assert(foo.length() ==3);

    printf("Testing SDL_DELAY timing\n");
    test_sdl_delay();
    
    printf("Testing partial entity updates\n");
    test_partial_entity_update();
    
    printf ("Testing vector\n");
    test_vector();

    printf ("Testing area\n");
    test_area();

    printf ("Testing shooting\n");
    test_shooting();
    
    printf ("Testing collision detection");
    test_collision_detection();

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

int test_sdl_delay(void) 
{
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        fprintf (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        exit (1);
    }
    fprintf (stderr, "SDL initialized.\n");
    
    Uint32 i, time1, time2;
    std::stringstream buf;
    
    for (i = 0; i < 30; ++i){
        time1 = SDL_GetTicks();
        SDL_Delay(i);
        time2 = SDL_GetTicks();
        buf << "endTicks: " << time2 << " - startTicks " << time1 << " = " << time2-time1 << " actual delay: " << i << "\n";
        console->log(buf.str());
    }
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
    Area *area = new Area(400, 400);
    Area *mini = new Area(100, 100);
    std::stringstream buf;

    Vector *v = new Vector();
    v->x = 100;
    v->y = -23;

    buf << "scale_x: " <<  area->scale_x(mini, v);
    console->log(buf.str());
    buf.str("");

    assert(area->scale_x(mini, v) == 25);

    assert(area->contains(v));

    v->x = 400;
    assert(!area->contains(v));

    assert(area->point_is_right(v));

    v->x = -330;
    assert(area->point_is_left(v));

    v->y = 300;
    assert(area->point_is_below(v));

    v->y = -300;
    assert(area->point_is_above(v));

}

int test_camera(void)
{
    Camera *cam = new Camera("camera1", 400, 400);
    Entity *ent = new Entity();
    Sector *sector = new Sector("anime");
    std::stringstream buf;

    ent->v->x = 5000;
    ent->v->y = 5000;

    Vector *p = new Vector();

    cam->position->x = 0;
    cam->position->y = 0;

    cam->set_from_screen_coords(p, 100, 100);

    buf << "pX: " << p->x << " pY: " << p->y;
    console->log(buf.str());
    buf.str("");

    assert(p->x == -100);
    assert(p->y == 100);

    sector->add_entity(ent);

    cam->follow(ent);

    buf << "X: " << cam->position->x << " Y: " << cam->position->y;

    console->log(buf.str());

    assert(cam->position->x == 4900);
    assert(cam->position->y == 4900);
}

int test_collision_detection(void)
{
    Sector *sector = new Sector("anime");
    
    Entity *ent = new Entity();
    ent->v->x = 0;
    ent->v->y = 0;
    sector->add_entity(ent);
    ent->log_info();

    ent = new Entity();
    ent->v->x = 0;
    ent->v->y = 0;
    sector->add_entity(ent);
    ent->log_info();

    sector->frameupdate_with_collisions();
}

int test_shooting(void)
{
    Sector *sector = new Sector("anime");
    Entity *ent = new Entity();
    ent->primary = new PlasmaCannon(ent);
    sector->add_entity(ent);

    assert(sector->entities.size() == 1);

    ent->primary->fire_shot();
    assert(sector->entities.size() == 2);

    ent->primary->fire_shot();
    assert(sector->entities.size() == 2);

    ent->primary->frameupdate();
    ent->primary->frameupdate();
    ent->primary->frameupdate();
    ent->primary->frameupdate();
    ent->primary->frameupdate();
    ent->primary->frameupdate();
    ent->primary->frameupdate();
    ent->primary->frameupdate();
    ent->primary->frameupdate();
    ent->primary->frameupdate();
    ent->primary->fire_shot();
    assert(sector->entities.size() == 3);
}
