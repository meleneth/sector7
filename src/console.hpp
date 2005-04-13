#ifndef ___console_inc
#define ___console_inc 1

#include<list>
#include<iostream> // Evil

#include<SDL.h>

#include<sstream>

#define MAKE_STRING( msg )  ( ((std::ostringstream&)(std::ostringstream() << msg)).str() )

class Console {
    public:
        // Public data members go here.
        Console::Console(Uint16 x, Uint16 y); // Constructor
        Console::~Console(); // Destructor

        void render(void);
        void log(std::string line);
        void box_log(std::string line);

        std::list<std::string> loglines;
        Uint16 xres, yres;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
