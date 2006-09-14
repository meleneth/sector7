/*Stop multiple inclusion */
#ifndef ___scoreboard_inc
#define ___scoreboard_inc 1


#include"SDL.h"


class ScoreBoard {
    public:
        // Public data members go here.
        Sint32 score;
        bool on;

        ScoreBoard(); // Constructor
        ~ScoreBoard(); // Destructor

        int render(void);
        int add(Sint16 myscore);
        int DrawDigit(int digit);
        int DrawLetter(int letter);
        int DrawDash(void);
        int DrawDot(void);
        int DrawNumAt(double num, Uint16 numdigits, Sint32 x, Sint32 y);
        int DrawStringAt(std::string msg, Uint16 numletters, Sint32 x, Sint32 y);

    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
