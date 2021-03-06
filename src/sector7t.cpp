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
std::stringstream buf;

int toy_test(void);
int test_partial_entity_update(void);
int test_entity_marshalling(void);
int test_shooting(void);
int test_camera(void);
int test_vector(void);
int test_area(void);
int test_sdl_delay(void);
int test_collision_detection(void);
int test_netServer_add_remove_ent(void);
int test_sector_add_remove_ent(void);

int main(int argc, char *argv[])
{
    console = new Console();
    console->print_logs = 1;

    load_textures(1);
    my_ship = NULL;

    std::string foo;
    foo = "Bar";
    assert(foo.length() ==3);
    
    console->log("Testing toy");
    toy_test();

    console->log("Testing SDL_DELAY timing");
    test_sdl_delay();
    
    console->log("Testing partial entity updates");
    test_partial_entity_update();
    
    console->log("Testing area");
    test_area();

    console->log("Testing shooting");
    test_shooting();
    
    console->log("Testing Sector::(add_ent | remove_ent)");
    test_sector_add_remove_ent();

    console->log("Testing NetServer::(add_ent | remove_ent)");
    test_netServer_add_remove_ent();

    console->log("Testing collision detection");
    test_collision_detection();

    console->log("Testing entity marshalling");
    test_entity_marshalling();

    console->log("Testing camera");
    test_camera();
    
    console->log("Testing vector");
    test_vector();
}

int toy_test(void)
{
    double num = -12345.6789;

    Sint32 int_part = trunc(num);

    double fract_part = num - (double)int_part;

    std::stringstream buf;
    buf << "int part: " << int_part << " fractional part " << fract_part;
    console->log(buf.str());
    buf.str("");
        
    char c = ' ';
    int i = (int) c;
    buf << c << "  " << i;
    console->log(buf.str());
    buf.str("");
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
    
    for (i = 0; i < 30; ++i){
        time1 = SDL_GetTicks();
        SDL_Delay(i);
        time2 = SDL_GetTicks();
        buf << "endTicks: " << time2 << " - startTicks " << time1 << " = " << time2-time1 << " actual delay: " << i;
        console->log(buf.str());
        buf.str("");
    }
}
int test_sector_add_remove_ent(void)
{
    std::list < Sector * >::iterator s;
    std::list < Entity * >::iterator e;
    
    Sector *sector1 = new Sector("anime");
    Sector *sector2 = new Sector("cowboy");
    Sector *sector3 = new Sector("bebop");
    
    sector1->attach_sector(sector2);
    sector1->attach_sector(sector3);
    sector2->attach_sector(sector3);
    
    Entity *ent = new Entity();
    ent->v->x = 0;
    ent->v->y = 0;
    
    sector1->add_entity(ent);
    sector1->list_ents();
    
    Entity *ent1 = new Entity();
    ent->v->x = 0;
    ent->v->y = 0;
    
    sector1->add_entity(ent1);
    sector1->list_ents();
    
    sector1->remove_ent(ent);
    sector1->list_ents();
    
    sector1->remove_ent(ent1);
    sector1->list_ents();
}

int test_netServer_add_remove_ent(void)
{
    NetServer *server = new NetServer(DEFAULT_PORT, "initialD");

}

int test_entity_marshalling(void)
{
    Entity *ent = new Entity();
    EntFull info;

    Sint32 foo = -50;

    foo = ntohl(htonl(foo));

    buf << "TILE_SHIP is " << (int) TILE_SHIP << " and TILE_NOTILE is " << (int) TILE_NOTILE;
    console->log(buf.str());
    buf.str("");

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

    bound->wrap_within(p);

    buf << "pX: " << p->x << " pY: " << p->y;
    console->log(buf.str());
    buf.str("");

    assert(p->x == 200);
    assert(p->y == 200);

    p->x = 513;
    p->y = 385;

    bound->wrap_within(p);

    buf << "pX: " << p->x << " pY: " << p->y;
    console->log(buf.str());
    buf.str("");

    assert(p->x == -512);
    assert(p->y == -384);

    Vector *t = new Vector();

    p->x = 100;
    p->y = 0;

    t->x = 0;
    t->y = 0;

    t->follow(p, 50);

    assert(t->x == 50);
    assert(t->y == 0);

    p->x = 4900;
    p->y = 0;

    t->x = 5000;
    t->y = 0;

    t->follow(p, 50);

    buf << "tX: " << t->x << " tY: " << t->y;
    console->log(buf.str());
    buf.str("");

    assert(t->x == 4950);
    assert(t->y == 0);

    p->x = 0;
    p->y = 100;

    t->x = 0;
    t->y = 0;

    t->follow(p, 50);

    buf << "tX: " << t->x << " tY: " << t->y;
    console->log(buf.str());
    buf.str("");

    assert(t->x == 0);
    assert(t->y == 50);

    p->x = 0;
    p->y = -100;

    t->x = 0;
    t->y = 0;

    t->follow(p, 50);

    buf << "tX: " << t->x << " tY: " << t->y;
    console->log(buf.str());
    buf.str("");

    assert(t->x == 0);
    assert(t->y == -50);

}

int test_area(void)
{
    Area *area = new Area(400, 400);
    Area *mini = new Area(100, 100);

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

    v->y = -300;
    assert(area->point_is_below(v));

    v->y = 300;
    assert(area->point_is_above(v));

}

int test_camera(void)
{
    Camera *cam = new Camera("camera1", 400, 400);
    Entity *ent = new Entity();
    Sector *sector = new Sector("anime");

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

    buf << "X: " << cam->position->x << " Y: " << cam->position->y;

    console->log(buf.str());
    buf.str("");

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
