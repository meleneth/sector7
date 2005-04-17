#include "console.hpp"
#include <ncurses.h>


// Public data members go here.
Console::Console() // Constructor
{
    xres=100;
    yres=10;
    box_log("Console Initialized");
}

Console::Console(Uint16 x, Uint16 y) // Constructor
{
    xres=x;
    yres=y;
    box_log("Console Initialized");
}
    
Console::~Console() // Destructor
{
}

void Console::render(void)
{
    std::list<std::string>::iterator i;
    Sint16 counter=yres-2;

    erase();

    for(i = loglines.begin() ; (i != loglines.end()) && counter != -1; ++i)
    {
        mvaddstr(counter, 0,  i->c_str());
        counter--;
    }
}

void Console::log(std::string line)
{
    loglines.push_front(line);
}

void Console::box_log(std::string line)
{
    std::string Border(line.length() + 2, '-');

    log("+" + Border + "+");
    log("| " + line + " |");
    log("+" + Border + "+");
}



// Private members go here.
// Protected members go here.
