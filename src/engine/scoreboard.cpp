#include "stdutil.hpp"
#include "scoreboard.hpp"
#include"map_defines.hpp"
#include<math.h>

#include"SDL.h"
#include"engine.hpp"

// Public data members go here.
ScoreBoard::ScoreBoard()	// Constructor
{
    score = 0;
    on = false;
}

ScoreBoard::~ScoreBoard()	// Destructor
{
}

int ScoreBoard::render(void)
{
    if (score < 0)
        glColor4f(1.0, 0, 0, 1);

    DrawNumAt(score, 9, 0, 0);
    return true;
}

int ScoreBoard::add(Sint16 myscore)
{
    score += myscore;
    return true;
}

int ScoreBoard::DrawDash()
{
    Texture *texture;
    texture = get_tex_id(TILE_DASHDOT);

    glBindTexture(GL_TEXTURE_2D, texture->GLtexID);	// Bind Our Texture

    glBegin(GL_QUADS);

    int digit = 0;
    glTexCoord2f(.5 * (digit + 1), 1);
    glVertex3f(-8, 8, 0.0);

    glTexCoord2f(.5 * (digit + 1), 0.0);
    glVertex3f(-8, -8, 0.0);

    glTexCoord2f(.5 * digit, 0.0);
    glVertex3f(8, -8, 0.0);

    glTexCoord2f(.5 * digit, 1.0);
    glVertex3f(8, 8, 0.0);

    glEnd();			// Done Drawing The Square

    return true;
}
int ScoreBoard::DrawDot()
{
    Texture *texture;
    texture = get_tex_id(TILE_DASHDOT);

    glBindTexture(GL_TEXTURE_2D, texture->GLtexID);	// Bind Our Texture

    glBegin(GL_QUADS);

    int digit = 1;
    glTexCoord2f(.5 * (digit + 1), 1);
    glVertex3f(-8, 8, 0.0);

    glTexCoord2f(.5 * (digit + 1), 0.0);
    glVertex3f(-8, -8, 0.0);

    glTexCoord2f(.5 * digit, 0.0);
    glVertex3f(8, -8, 0.0);

    glTexCoord2f(.5 * digit, 1.0);
    glVertex3f(8, 8, 0.0);

    glEnd();			// Done Drawing The Square

    return true;
}

int ScoreBoard::DrawDigit(int digit)
{
    Texture *texture;
    
    digit = digit % 10;		//zapow
    texture = get_tex_id(TILE_NUMBERS);

    glBindTexture(GL_TEXTURE_2D, texture->GLtexID);	// Bind Our Texture

    glBegin(GL_QUADS);

    glTexCoord2f(.1 * (digit + 1), 1);
    glVertex3f(-8, 8, 0.0);

    glTexCoord2f(.1 * (digit + 1), 0.0);
    glVertex3f(-8, -8, 0.0);

    glTexCoord2f(.1 * digit, 0.0);
    glVertex3f(8, -8, 0.0);

    glTexCoord2f(.1 * digit, 1.0);
    glVertex3f(8, 8, 0.0);

    glEnd();			// Done Drawing The Square

    return true;
}

int ScoreBoard::DrawLetter(int letter)
{
    Texture *texture;
    
    texture = get_tex_id(TILE_ALPHA);

    glBindTexture(GL_TEXTURE_2D, texture->GLtexID);	// Bind Our Texture

    double scale = 1.0/26.0;

    glBegin(GL_QUADS);
    
    glTexCoord2f(scale * (letter + 1), 1);
    glVertex3f(-8, 8, 0.0);

    glTexCoord2f(scale * (letter + 1), 0.0);
    glVertex3f(-8, -8, 0.0);

    glTexCoord2f(scale * letter, 0.0);
    glVertex3f(8, -8, 0.0);

    glTexCoord2f(scale * letter, 1.0);
    glVertex3f(8, 8, 0.0);

    glEnd();			// Done Drawing The Square

    return true;
    
}

int ScoreBoard::DrawNumAt(double num, Uint16 numdigits, Sint32 x, Sint32 y){
	Sint32 value = 1;

    Sint32 integer_part;
    double fraction_part;
    Uint32 tenth, hunth;

    integer_part = (Sint32) trunc(num);
    fraction_part = num - (double) integer_part;    
    integer_part = abs(integer_part);
    if (fraction_part < 0) fraction_part *= -1.0;

    tenth = (Uint32) trunc(fraction_part * 10);
    fraction_part = fraction_part * 10 - tenth;
    hunth = (Uint32) trunc(fraction_part * 10);

    glLoadIdentity();
    glTranslatef(x, y, 0);
    
    DrawDigit(hunth);
    glTranslatef(16, 0, 0);
    DrawDigit(tenth);
    glTranslatef(16, 0, 0);
    DrawDot();
    glTranslatef(16, 0, 0);
    while (numdigits--) {
        if (integer_part < value) {
            DrawDigit(0);
            glTranslatef(16, 0, 0);
            value=value*10;
        } else {
            DrawDigit(m_round(integer_part / value));
            glTranslatef(16, 0, 0);
	        value=value*10;
        }
    }
    if (num < 0){
        DrawDash();
    }
    return true;
}

int ScoreBoard::DrawStringAt(std::string msg, Uint16 numletters, Sint32 x, Sint32 y)
{
    glLoadIdentity();
    glTranslatef(x, y, 0);
    
    for (int i = 0; i < numletters; ++i){
        DrawLetter(((int) msg[i]) - 97);
        glTranslatef(-16, 0, 0);
    }
    return true; 
}

 
// Private members go here.

// Protected members go here.
