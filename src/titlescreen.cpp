#include "stdutil.hpp"
#include "titlescreen.hpp"

#include"renderer.hpp"


// Public data members go here.
TitleScreen::TitleScreen(void):Entity(E_NEUTRAL)	// Constructor
{
    texture = get_tex_id(TILE_TITLESCREEN);
    health=500;
    v->x=0;
    v->y=0;
    v->power=0;
    rotation=0;
}

TitleScreen::~TitleScreen()	// Destructor
{
}

int TitleScreen::chkDeath(void){
	health--;
	if(health==0) return true;
	return false;
}


int TitleScreen::chkCollision(Uint16 ent_type, Sint16 pointx, Sint16 pointy, Sint16 mysize){
	return false;
}

void TitleScreen::render(void){
    glLoadIdentity();
    glTranslatef(v->x, v->y, 0);
    glRotatef(rotation, 0, 0, 1);
    if(taken_damage){
        glColor4f(1.0,0.0,0.0,1.0);
        texture->DrawGLSquare(size);
        glColor4f(1.0,1.0,1.0,1.0);
        taken_damage--;
    } else {
        texture->DrawGLSquare(200);
    }
//    texture->DrawGLSquare(200);
}

// Private members go here.

// Protected members go here.
