#ifndef ___area_inc
#define ___area_inc 1

#include"SDL.h"
#include"vector.hpp"

class Area {
    public:
        // Public data members go here.
        Area::Area(double width, double height); // Constructor
        Area::~Area(); // Destructor

        bool contains(Vector *p);

        double x, y, width, height;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
