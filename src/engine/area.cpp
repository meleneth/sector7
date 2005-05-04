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
    return (abs(p->x) < width/2) 
        && (abs(p->y) < height/2);
}

void Area::follow(Vector *follow, Vector *modify)
{
    if(contains(follow))
            return;

    if(point_is_left(follow))
            modify->x = follow->x - width;

    if(point_is_right(follow))
            modify->x = follow->x + width;

    if(point_is_above(follow))
            modify->y = follow->y - height;

    if(point_is_below(follow))
            modify->y = follow->y + height;
}

bool Area::point_is_left(Vector *p)
{
        return (x - width) > p->x;
}

bool Area::point_is_right(Vector *p)
{
        return (x + width) < p->x;
}

bool Area::point_is_above(Vector *p)
{
        return (y - height) > p->y;
}

bool Area::point_is_below(Vector *p)
{
        return (y + height) < p->y;
}
// Private members go here.
// Protected members go here.
