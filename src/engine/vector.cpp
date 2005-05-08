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
    if (x < -(boundary->halfwidth)) 
        x = (boundary->halfwidth);

    if (x > (boundary->halfwidth))  
        x = -(boundary->halfwidth);

    if (y < -(boundary->halfheight)) 
        y = (boundary->halfheight);

    if (y > (boundary->halfheight))  
        y = -(boundary->halfheight);
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
