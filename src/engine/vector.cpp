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

double Vector::calc_angle(Vector *v)
{
    return calc_angle(v->x, v->y);
}

double Vector::calc_angle(double targx, double targy)
{
    double myangle;
    double leg1, leg2;

    leg1 = targy - y; 
    leg2 = targx - x;

    return atan(leg2 / leg1) ;
}

double Vector::distance(Vector *target)
{
    return abs(m_round(hypot(x - target->x, y - target->y)));
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

void Vector::follow(Vector *v, double leash_length)
{
    double d = distance(v);

    if( leash_length > d )
        return;

    double angle = calc_angle(v);

    x = ((d - leash_length) * cos(angle * (PI/180)));
    y = ((d - leash_length) * sin(angle * (PI/180)));
    
}

void Vector::set_from(Vector *v)
{
    angle = v->angle;
    power = v->power;
    rotation = v->rotation;
    x=v->x;
    y=v->y;
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
    x = x1 + random - ((x2 - x1)/2);
    random = rand();
    random = random % (int)(floor(x2 - x1));
    y = y1 + random - ((y2 - y1)/2);
}

// Private members go here.

// Protected members go here.
