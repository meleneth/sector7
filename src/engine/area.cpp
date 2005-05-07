#include "area.hpp"

// Public data members go here.
Area::Area(double width, double height) // Constructor
{
    this->width = width;
    this->height = height;
    this->halfwidth = width/2;
    this->halfheight = height/2;
    this->x = 0;
    this->y = 0;
}
    
Area::~Area() // Destructor
{
}

bool Area::contains(Vector *p)
{
    if(p->x < x - halfwidth)
        return 0;
    if(p->x > x + halfwidth)
        return 0;
    if(p->y < y - halfheight)
        return 0;
    if(p->y < y - halfheight)
        return 0;

    return 1;
}

void Area::follow(Vector *follow, Vector *modify)
{
    if(contains(follow))
            return;

    if(point_is_left(follow))
            modify->x = follow->x - halfwidth;

    if(point_is_right(follow))
            modify->x = follow->x + halfwidth;

    if(point_is_above(follow))
            modify->y = follow->y - halfheight;

    if(point_is_below(follow))
            modify->y = follow->y + halfheight;
}

bool Area::point_is_left(Vector *p)
{
        return (x - halfwidth) > p->x;
}

bool Area::point_is_right(Vector *p)
{
        return (x + halfwidth) < p->x;
}

bool Area::point_is_above(Vector *p)
{
        return (y - halfheight) > p->y;
}

bool Area::point_is_below(Vector *p)
{
        return (y + halfheight) < p->y;
}
// Private members go here.
// Protected members go here.
