#include"SDL.h"
#include"math.h"

Sint32 m_round(double value)
{
    return (Sint32) floor(value < 0 ? value - 0.5 : value + 0.5);
}

Sint32 m_trunc(double value)
{
    return (Sint32) floor(value);
}

