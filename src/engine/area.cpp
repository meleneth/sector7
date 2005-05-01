#include "area.hpp"

// Public data members go here.
Area::Area(double width, double height) // Constructor
{
    this->width = width;
    this->height = height;
    this->x = 0;
    this->y = 0;
}
    
Area::~Area() // Destructor
{
}

bool Area::contains(Vector *p)
{
    return ((x - p->x) < width) 
        && ((y - p->y) < height);
}
// Private members go here.
// Protected members go here.
