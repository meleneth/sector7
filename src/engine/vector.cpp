#include "stdutil.hpp"
#include "vector.hpp"
#include "area.hpp"

Sint32 m_trunc(double value);

// Public data members go here.
Vector::Vector ()		// Constructor
{
    angle=0; 
    power=0; 
    rotation=0;
    x=0;
    y=0;
}

Vector::Vector(Vector *v)
{
    set_from(v);
}

Vector::~Vector ()		// Destructor
{
}

double Vector::calc_angle(double targx, double targy)
{
    double myangle;
    double leg1, leg2;

    leg1 = targy - y; 
    leg2 = targx - x;

    myangle  = atan(leg1 / leg2) ;

    return (leg2 < 0
        ? myangle * (180 / M_PI) - 180 
        : myangle * (180/M_PI));
}

void Vector::aim(double targx, double targy)
{
    angle = m_trunc(calc_angle(targx, targy));
}

void Vector::aim(Vector *target)
{
    aim(target->x, target->y);
}

void Vector::update_location(void)
{
    x += power * cos(angle  * (PI / 180));
    y += power * sin(angle  * (PI / 180));
}

void Vector::set_from_screen_coords(double screen_x, double screen_y, Uint32 screen_width, Uint32 screen_height)
{
    x = screen_x - (screen_width/2);
    y = screen_y - (screen_height/2);
}

void Vector::set_from(Vector *v)
{
    angle = v->angle;
    power = v->power;
    rotation = v->rotation;
    x=v->x;
    y=v->y;
}

void Vector::bounds_check(Area *boundary)
{
    if (x < -(boundary->width/2)) x = (boundary->width/2);
    if (x > (boundary->width/2))  x = -(boundary->width/2);

    if (y < -(boundary->height/2)) y = (boundary->height/2);
    if (y > (boundary->height/2))  y = -(boundary->height/2);
}

void Vector::accelerate(Vector *v)
{
    //angle = v->angle;
    power += v->power;
}

double stepped_diff(double steps, double src, double dest)
{
    return src + (dest - src) / steps;
}

void Vector::random_location(double x1, double y1, double x2, double y2)
{
    Sint32 random = rand();
    random = random % (int)(floor(x2 - x1));
    x = x1 + random;;
    random = rand();
    random = random % (int)(floor(x2 - x1));
    y = y1 + random;
}

// Private members go here.

// Protected members go here.
