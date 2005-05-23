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

int ScoreBoard::DrawDigit(int digit)
{
    Texture *texture;

    digit = digit % 10;		//zapow
    texture = get_tex_id(TILE_NUMBERS);

    glBindTexture(GL_TEXTURE_2D, texture->GLtexID);	// Bind Our Texture

    glBegin(GL_QUADS);

    glTexCoord2f((1.0/12.0) * (digit + 1), 1);
    glVertex3f(-8, 8, 0.0);

    glTexCoord2f((1.0/12.0) * (digit + 1), 0.0);
    glVertex3f(-8, -8, 0.0);

    glTexCoord2f((1.0/12.0) * digit, 0.0);
    glVertex3f(8, -8, 0.0);

    glTexCoord2f((1.0/12.0) * digit, 1.0);
    glVertex3f(8, 8, 0.0);

    glEnd();			// Done Drawing The Square

    return true;
}

int ScoreBoard::DrawNumAt(Sint32 num, Uint16 numdigits, Sint32 x, Sint32 y){
	 Sint32 value = 1;

    Sint32 pScore;
    if (num < 0)
        glColor4f(1.0, .4, .4, 1);

    pScore = num;

    pScore = abs(pScore);
    glLoadIdentity();
    glTranslatef(x, y, 0);

    while (numdigits--) {
        if (pScore < value) {
            DrawDigit(0);
            glTranslatef(16, 0, 0);
        value=value*10;
        } else {
            DrawDigit(m_round(pScore / value));
            glTranslatef(16, 0, 0);
	 value=value*10;

        }
    }
    return true;

}

// Private members go here.

// Protected members go here.
