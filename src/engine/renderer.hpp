/*Stop multiple inclusion */
#ifndef ___renderer_inc
#define ___renderer_inc 1

#include"SDL.h"

#include"video.hpp"
#include"texture.hpp"

#include"camera.hpp"

class Renderer {
    public:
        // Public data members go here.
        Renderer(Uint32 xres, Uint32 yres); // Constructor
        ~Renderer(); // Destructor
        void swap_buffers(void);
        int RenderFrame(Camera *camera);
        void ClearScreen(void);

    private:
        // Private members go here.
        Video *board;
    protected:
        // Protected members go here.
};

extern Renderer *renderer;

#endif
