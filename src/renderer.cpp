#include "stdutil.hpp"
#include "renderer.hpp"
#include "globals.hpp"
#include "map_defines.hpp"
#include"entitymgr.hpp"
#include"texture.hpp"
#include"engine.hpp"

#include <GL/gl.h>


// Public data members go here.
Renderer::Renderer()		// Constructor
{
    board = new Video();
    load_textures();
}

Renderer::~Renderer()		// Destructor
{
}

int Renderer::RenderFrame(void)
{
    GLenum gl_error;
    static int reticle_angle = 0;

    ClearScreen();
    glColor4f(1, 1, 1, .9);
    bg_particles->render();

    glColor4f(1, 1, 1, 1);
    entmgr->render();
    fg_particles->render();
    if(player1){
        glLoadIdentity();
        glTranslatef(player1->v->x, player1->v->y, 0);
        glRotatef(player1->v->angle, 0.0, 0.0, 1.0);
        glLoadIdentity();
        glTranslatef(player1->cursor->x, player1->cursor->y, 0);

        reticle_angle += 4;
        if (reticle_angle > 360)
            reticle_angle = 0;
        glRotatef(reticle_angle, 0, 0, 1);
        glColor4f(0, 1, 0, .65);
        get_tex_id(TILE_RETICLE)->DrawGLSquare(16);

        glColor4f(0, 1, 0, 1);
        scoreboard->render();
        scoreboard->DrawNumAt(player1->level, 3, -HALFXRES+50, 10);
        scoreboard->DrawNumAt(player1->health, 6, 0, 10);
        glColor4f(1, 1, 1, 1);
    player1->render();
    }
    SDL_GL_SwapBuffers();

    /* Check for error conditions. */
    gl_error = glGetError();

    if (gl_error != GL_NO_ERROR) {
        fprintf(stderr, "KarmaRender: OpenGL error: %d\n", gl_error);
    }
    return true;
}


void Renderer::ClearScreen(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



// Private members go here.

// Protected members go here.
