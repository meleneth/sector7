#include "stdutil.hpp"
#include "texture.hpp"
#include"SDL_opengl.h"
#include "glpng.h"

std::list < Texture * > textures;

// Public data members go here.
Texture::Texture ()
{
}

Texture::Texture (int dummy, char *filename, TileNum tilenum)	// Constructor
{
    if(!dummy) {
        LoadImage (filename);
    }
    this->tilenum = tilenum;
}

Texture::~Texture ()
{
}

int Texture::LoadImage (char *filename)
{
    pngInfo tmpInfo;
    GLtexID = pngBind (filename, PNG_NOMIPMAPS, PNG_ALPHA, &tmpInfo, GL_CLAMP, GL_LINEAR, GL_LINEAR);
    if (GLtexID == 0)
    {
        printf ("Error trying to load %s\n", filename);
        exit (1);
    }
    width = tmpInfo.Width/2;
    height = tmpInfo.Height/2;
    std::stringstream logmsg;
    logmsg << "Loaded (" << width << "x" << height << ") into glID " << GLtexID << " from " << filename;
    console->log(logmsg.str());
    return true;
}

void Texture::DrawGLSquare (Sint16 size)
{
    glBindTexture (GL_TEXTURE_2D, GLtexID);	// Bind Our Texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size, size, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(size, size, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(size, -size, 0.0);
    glEnd ();			// Done Drawing The Square
}

void Texture::DrawGL ()
{
    glBindTexture (GL_TEXTURE_2D, GLtexID);	// Bind Our Texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width, -height, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-width, height, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(width, height, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(width, -height, 0.0);
    glEnd ();			// Done Drawing The Square
}

void load_textures(int dummy)
{
    textures.push_front(new Texture(dummy, "../graphics/sprites/explosion.png", TILE_EXPLOSION));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/ship.png", TILE_SHIP));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/rock1.png", TILE_ROCK1));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/rock2.png", TILE_ROCK2));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/rock3.png", TILE_ROCK3));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/rock4.png", TILE_ROCK4));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/rock5.png", TILE_ROCK5));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/rock6.png", TILE_ROCK6));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/SuperUp.png", TILE_SUPERPOWERUP));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/reticle.png", TILE_RETICLE));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/particle.png", TILE_PARTICLE));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/beamw.png", TILE_BEAMW));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/rocket.png", TILE_ROCKET));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/digits.png", TILE_NUMBERS));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/notex.png", TILE_NOTILE));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/powerup.png", TILE_POWERUP));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/shield.png", TILE_SHIELD));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/shipshield.png", TILE_SHIPSHIELD));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/laser.png", TILE_LASER));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/levelup.png", TILE_LEVELUP));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/robot.png", TILE_ROBOT));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/city/road.png", TILE_ROAD));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/city/building.png", TILE_BUILDING));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/smoke.png", TILE_SMOKE));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/boss/minerbot/head.png", TILE_MINERBOTHEAD));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/boss/minerbot/claw.png", TILE_MINERBOTCLAW));                 
    textures.push_front(new Texture(dummy, "../graphics/sprites/boss/minerbot/arm.png", TILE_MINERBOTARM));                 
    textures.push_front(new Texture(dummy, "../graphics/menu/newgame.png", TILE_NEWGAME));                 
    textures.push_front(new Texture(dummy, "../graphics/menu/quit.png", TILE_QUIT));                 
    textures.push_front(new Texture(dummy, "../graphics/screens/titlescreen.png", TILE_TITLESCREEN));                 
    textures.push_front(new Texture(dummy, "../graphics/screens/galaxies.png", TILE_GALAXIES));                 
}

Texture *get_tex_id(TileNum tile_id)
{
    std::list < Texture * >::iterator i;
    std::stringstream(buf);
    buf << "Looking up: " << (int) tile_id;
    console->log(buf.str());
    for(i = textures.begin(); i != textures.end(); ++i){
        if((*i)->tilenum == tile_id){
            console->log("Looked up texture");
            return *i;
        }
    }
    console->fatal("could not find texture in get_tex_id");

}
// Private members go here.

// Protected members go here.
