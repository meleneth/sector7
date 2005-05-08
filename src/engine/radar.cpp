#include "radar.hpp"
#include"SDL_opengl.h"

#define P_SIZE 1

// Public data members go here.
Radar::Radar(Area *a, Area *r) // Constructor
{
    actual_size = a;
    rendered_size = r;
    texture = get_tex_id(TILE_WHITE);
}
    
Radar::~Radar() // Destructor
{
}

void Radar::blip(Vector *p)
{
    glColor4f(1, 1, 1, .75);


    glLoadIdentity();
    glTranslatef(actual_size->scale_x(rendered_size, p),
                 actual_size->scale_y(rendered_size, p) , 0);

    texture->DrawGLSquare(P_SIZE);

}

// Private members go here.
// Protected members go here.
