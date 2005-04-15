/*Stop multiple inclusion */
#ifndef ___renderer_inc
#define ___renderer_inc 1

#include"SDL.h"

#include"video.hpp"
#include"texture.hpp"

class Renderer {
    public:
        // Public data members go here.
        Renderer::Renderer(); // Constructor
        Renderer::~Renderer(); // Destructor
        int RenderFrame(void);
        void ClearScreen(void);

    private:
        // Private members go here.
        Video *board;
    protected:
        // Protected members go here.
};

extern Renderer *renderer;

#endif
