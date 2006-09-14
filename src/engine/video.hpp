/*Stop multiple inclusion */
#ifndef ___video_inc
#define ___video_inc 1

#include"SDL_opengl.h"

#include"SDL.h"

class Video {
    public:
        // Public data members go here.
        Video(Uint32 xres, Uint32 yres); // Constructor
        ~Video(); // Destructor
    private:
        void InitGL(int bpp, int fullscreen, float gamma, Uint32 xres, Uint32 yres);
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
