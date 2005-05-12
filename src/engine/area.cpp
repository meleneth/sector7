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
    if(p->x < x - halfwidth)
        return 0;
    if(p->x > x + halfwidth)
        return 0;
    if(p->y < y - halfheight)
        return 0;
    if(p->y > y + halfheight)
        return 0;

    return 1;
}

void Area::follow(Vector *follow, Vector *modify, double leash_length)
{
    double distance = follow->distance(modify);
    if( leash_length > distance )
        return;
    
    double angle = follow->calc_angle(modify);

    modify->x += ((distance - leash_length) * cos(angle * (PI/180)));
    modify->y += ((distance - leash_length) * sin(angle * (PI/180)));
}

bool Area::point_is_left(Vector *p)
{
        return (x + halfwidth) > p->x;
}

bool Area::point_is_right(Vector *p)
{
        return (x - halfwidth) < p->x;
}

bool Area::point_is_above(Vector *p)
{
        return (y + halfheight) > p->y;
}

bool Area::point_is_below(Vector *p)
{
        return (y - halfheight) < p->y;
}

double Area::scale_x(Area *target, Vector *p)
{
    return (p->x -x)  / (width / target->width);
}

double Area::scale_y(Area *target, Vector *p)
{
    return  (p->y - y) / (height / target->height);
}

// Private members go here.
// Protected members go here.
