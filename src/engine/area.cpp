#include "area.hpp"
#include"globals.hpp"

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
    if(point_is_left(p))
        return 0;
    if(point_is_right(p))
        return 0;
    if(point_is_above(p))
        return 0;
    if(point_is_below(p))
        return 0;

    return 1;
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
        return (y + halfheight) < p->y;
}

bool Area::point_is_below(Vector *p)
{
        return (y - halfheight) > p->y;
}

double Area::scale_x(Area *target, Vector *p)
{
    return (p->x -x)  / (width / target->width);
}

double Area::scale_y(Area *target, Vector *p)
{
    return  (p->y - y) / (height / target->height);
}

void Area::wrap_within(Vector *p)
{
    if (point_is_above(p)) 
        p->y = y - halfheight;

    if (point_is_below(p)) 
        p->y = y + halfheight;

    if (point_is_right(p)) 
        p->x = x - halfwidth;

    if (point_is_left(p)) 
        p->x = x + halfwidth;

}

// Private members go here.
// Protected members go here.
