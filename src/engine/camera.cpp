#include "camera.hpp"
#include"globals.hpp"

// Public data members go here.
Camera::Camera(std::string sector_id, Uint32 xres, Uint32 yres): Sector(sector_id) // Constructor
{
    console->log(sector_id);
    visible_area = new Area(xres/2, yres/2);
    inner_bound = new Area(xres/4, yres/4);
    position = new Vector();
}
    
Camera::~Camera() // Destructor
{
}

void Camera::follow(Entity *bird)
{
    entities = ((Sector *)bird->sector)->entities;
   
    inner_bound->x = position->x;
    inner_bound->y = position->y;
    inner_bound->follow(bird->v, this->position);
}

// Private members go here.
// Protected members go here.
