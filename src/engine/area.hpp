#ifndef ___area_inc
#define ___area_inc 1

#include"SDL.h"
#include"vector.hpp"
#include"stdlib.h"
class Vector;
class Area {
    public:
        // Public data members go here.
        Area(double width, double height); // Constructor
        ~Area(); // Destructor

        bool contains(Vector *p);
        void wrap_within(Vector *p);

        bool point_is_below(Vector *p);
        bool point_is_above(Vector *p);
        bool point_is_left(Vector *p);
        bool point_is_right(Vector *p);
        double scale_x(Area *target, Vector *p);
        double scale_y(Area *target, Vector *p);


        double x, y, width, height, halfwidth, halfheight;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
