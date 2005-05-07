#include "stdutil.hpp"
#include "renderer.hpp"
#include "globals.hpp"
#include "map_defines.hpp"
#include"entitymgr.hpp"
#include"texture.hpp"
#include"engine.hpp"
#include"camera.hpp"

#include"SDL_opengl.h"

// Public data members go here.
Renderer::Renderer(Uint32 xres, Uint32 yres)		// Constructor
{
    board = new Video(xres, yres);
    load_textures(0);
}

Renderer::~Renderer()		// Destructor
{
}

int Renderer::RenderFrame(Camera *camera)
{
    static int reticle_angle = 0;

    ClearScreen();
    
    glColor4f(1, 1, 1, 1);
    camera->render();
    return true;
}

void Renderer::swap_buffers(void)
{
    GLenum gl_error;
    SDL_GL_SwapBuffers();

    /* Check for error conditions. */
    gl_error = glGetError();

    if (gl_error != GL_NO_ERROR) {
        fprintf(stderr, "KarmaRender: OpenGL error: %d\n", gl_error);
    }
}


void Renderer::ClearScreen(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



// Private members go here.

// Protected members go here.
