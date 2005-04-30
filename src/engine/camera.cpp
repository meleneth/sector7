#include "camera.hpp"
#include"globals.hpp"

// Public data members go here.
Camera::Camera(std::string sector_id): Sector(sector_id) // Constructor
{
    console->log(sector_id);
    visible_area = new Area(800,800);
}
    
Camera::~Camera() // Destructor
{
}

void Camera::follow(Entity *bird, Area *size)
{
    entities = ((Sector *)bird->sector)->entities;
    //if(position.x > bird->x)  position.x = bird->x
}

// Private members go here.
// Protected members go here.
