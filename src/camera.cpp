#include "camera.hpp"

// Public data members go here.
Camera::Camera(std::string sector_id): Sector(sector_id) // Constructor
{
    visible_area = new Area(800,800);
}
    
Camera::~Camera() // Destructor
{
}

void Camera::follow(Entity *bird, Area *size)
{
    //if(position.x > bird->x)  position.x = bird->x
}

// Private members go here.
// Protected members go here.
