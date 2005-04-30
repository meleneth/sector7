/*Stop multiple inclusion */
#ifndef ___texture_inc
#define ___texture_inc 1

#include<list>

#include"SDL.h"

#include"SDL_opengl.h"

#include"map_defines.hpp"



class Texture {
    public:
        // Public data members go here.
        GLuint GLtexID;
        TileNum tilenum;
        Uint16 width;
        Uint16 height;

        Texture::Texture(void);
        Texture::Texture(int dummy, char *filename, TileNum tilenum); // Constructor
        int Texture::LoadImage(char *filename);
        Texture::~Texture(); // Destructor
        int generate(void);
        void DrawGLSquare(Sint16 size);
        void DrawGL(void);
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};


void load_textures(int dummy);

Texture *get_tex_id(TileNum tile_id);

#endif
