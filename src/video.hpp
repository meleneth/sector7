/*Stop multiple inclusion */
#ifndef ___video_inc
#define ___video_inc 1

#include <GL/gl.h>

#include"SDL.h"

class Video {
    public:
        // Public data members go here.
        Video::Video(void); // Constructor
        Video::~Video(); // Destructor
    private:
        void Video::InitGL(int bpp, int fullscreen, float gamma);
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
