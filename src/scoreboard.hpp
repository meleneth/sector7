/*Stop multiple inclusion */
#ifndef ___scoreboard_inc
#define ___scoreboard_inc 1


#include"SDL.h"

class ScoreBoard {
    public:
        // Public data members go here.
        Sint32 score;

        ScoreBoard::ScoreBoard(); // Constructor
        ScoreBoard::~ScoreBoard(); // Destructor

        int render(void);
        int add(Sint16 myscore);
        int DrawDigit(int digit);
        int DrawNumAt(Sint32 num, Uint16 numdigits, Sint32 x, Sint32 y);

    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
