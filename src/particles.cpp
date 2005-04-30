#include "stdutil.hpp"
#include "particles.hpp"

#include<math.h>

Particle::Particle():red(1.0),green(1.0),blue(1.0),alpha(1.0)	// Constructor
{
    v = new Vector();
}

Particle::~Particle()	// Destructor
{
    delete v;
}

// Public data members go here.
ParticleSystem::ParticleSystem()	// Constructor
{
}

ParticleSystem::~ParticleSystem()	// Destructor
{
}

void ParticleSystem::frameupdate(void)
{
    std::list < Particle * >::iterator i;
    std::list < Particle *> dead_parts;

    for (i = particles.begin() ; i != particles.end() ; ++i){
        Particle *p = *i;
        p->v->update_location();
        p->lifespan--;
        if(p->lifespan == 0){
            dead_parts.push_front(p);
        }
    }
    for (i = dead_parts.begin() ; i != dead_parts.end() ; ++i){
        Particle *p = *i;
        particles.remove(p);
        delete p;
    }

}

void ParticleSystem::render(void)
{

    Uint16 particlenum;
    std::list < Particle * >::iterator i;
    Particle *p;    
    glLoadIdentity();
    
    
    glDisable(GL_TEXTURE_2D);
    glColor4f(1.0, 1.0, 1.0,.75);

    for (i = particles.begin() ; i != particles.end() ; ++i){
        p = *i;
        glTranslatef(p->v->x, p->v->y, 0.0);
        glBegin(GL_TRIANGLE_STRIP);  
            glVertex3f(p->v->x+5, p->v->y+5,0);
            glVertex3f(p->v->x-5, p->v->y+5,0);
            glVertex3f(p->v->x+5, p->v->y-5,0);
            glVertex3f(p->v->x-5, p->v->y-5,0);
        glEnd();
    }

    glColor4f(1.0, 1.0, 1.0, 1.0);
    
    //glTranslatef(0, 0.0f, -2.0f);
     glEnable(GL_TEXTURE_2D);
}

// Private members go here.

// Protected members go here.
