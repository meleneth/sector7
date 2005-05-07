#include "camera.hpp"
#include"globals.hpp"

// Public data members go here.
Camera::Camera(std::string sector_id, Uint32 xres, Uint32 yres): Sector(sector_id) // Constructor
{
    console->log(sector_id);
    visible_area = new Area(xres, yres);
    inner_bound = new Area(xres/2, yres/2);
    position = new Vector();
}
    
Camera::~Camera() // Destructor
{
}

void Camera::follow(Entity *bird)
{
    inner_bound->follow(bird->v, this->position);
}

// Private members go here.
// Protected members go here.
