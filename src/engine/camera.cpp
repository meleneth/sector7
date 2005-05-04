#include "camera.hpp"
#include"globals.hpp"

// Public data members go here.
Camera::Camera(std::string sector_id, Uint32 xres, Uint32 yres): Sector(sector_id) // Constructor
{
    console->log(sector_id);
    visible_area = new Area(xres, yres);
}
    
Camera::~Camera() // Destructor
{
}

void Camera::follow(Entity *bird)
{
    entities = ((Sector *)bird->sector)->entities;
    position->x = bird->v->x;
    position->y = bird->v->y;
}

// Private members go here.
// Protected members go here.
