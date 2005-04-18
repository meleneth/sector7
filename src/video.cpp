#include "stdutil.hpp"
#include "video.hpp"



// Public data members go here.
Video::Video (void)		// Constructor
{
  InitGL (16, 0, 0.0);
}

Video::~Video ()		// Destructor
{
}


void Video::InitGL (int bpp, int fullscreen, float gamma)
{
    Uint32 video_flags;
    int w = XRES;
    int h = YRES;

    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        fprintf (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        exit (1);
    }
    fprintf (stderr, "SDL initialized.\n");

    video_flags = SDL_OPENGL;
    //-- Initialize display
    SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
    if (SDL_SetVideoMode (w, h, bpp, video_flags) == NULL)
    {
        fprintf (stderr, "Couldn't set GL mode: %s\n", SDL_GetError ());
        SDL_Quit ();
        exit (1);
    }
    else
        fprintf (stderr, "video mode set.\n");

    printf("Init: [---%d bpp fullscreen(%d) %f gamma---]\n", bpp, fullscreen, gamma);


    glLoadIdentity ();
    glMatrixMode (GL_PROJECTION);

    glOrtho (-HALFXRES, HALFXRES, YRES, 0, 20, -20);
    printf ("Init: [%d bpp fullscreen(%d) %f gamma]\n", bpp, fullscreen, gamma);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    glViewport (0, 0, XRES, YRES);
    glDisable (GL_DEPTH_TEST);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glDepthFunc (GL_LEQUAL);
    glColor4f (1.0f, 1.0f, 1.0f, 1);	// Full Brightness, 50% Alpha ( NEW )
    //        glBlendFunc(GL_SRC_ALPHA,GL_ONE);               // Blending Function For Translucency Based On Source Alpha Value ( NEW )
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //glEnable(GL_SET);
    //  glShadeModel(GL_SMOOTH);
    SDL_WM_SetCaption ("Codename: Last Defense", "lastdefense");

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    SDL_ShowCursor(0);
}