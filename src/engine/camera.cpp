#include "camera.hpp"
#include"globals.hpp"
#include<sstream>

// Public data members go here.
Camera::Camera(std::string sector_id, Uint32 xres, Uint32 yres): Sector(sector_id) // Constructor
{
    console->log(sector_id);
    visible_area = new Area(xres, yres);
    inner_bound = new Area(xres/2, yres/2);
    position = new Vector();
    radar = new Radar(visible_area, inner_bound);
}
    
Camera::~Camera() // Destructor
{
}

void Camera::render(void)
{
    std::list < Entity * >::iterator i;
    num_ents = 0;

    glColor4f (1, 1, 1, 1);

    std::list < Sector * >::iterator s;
    std::list < Entity * >::iterator e;
    
    for (s = attached_sectors.begin(); s != attached_sectors.end(); s++) {
        for (e = (*s)->visible_entities.begin(); e != (*s)->visible_entities.end(); e++) {
            visible_entities.push_front(*e);
        }
    }
    for (i = visible_entities.begin (); i != visible_entities.end (); ++i)
    {
          (*i)->render(position);
          radar->blip((*i)->v);
          num_ents++;
    }
}

void Camera::remove_ent(Entity *entity)
{
    std::list < Sector * >::iterator s;
    
    visible_entities.remove(entity);
    for (s = attached_sectors.begin(); s != attached_sectors.end(); s++) {
        (*s)->visible_entities.remove(entity);
    }
}

void Camera::follow(Entity *bird)
{
    position->follow(bird->v, inner_bound->width / 4);
}

void Camera::set_from_screen_coords(Vector *v, double screen_x, double screen_y)
{
    v->x = position->x + screen_x - visible_area->halfwidth;
    v->y = position->y - screen_y + visible_area->halfheight;
}



// Private members go here.
// Protected members go here.
