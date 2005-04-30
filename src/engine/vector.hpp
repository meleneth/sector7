/*Stop multiple inclusion */
#ifndef ___vector_inc
#define ___vector_inc 1

#include"SDL.h"
#include"types.hpp"

class Vector {
    public:
        // Public data members go here.
        Vector::Vector();	// Constructor
        Vector::Vector(Vector *copy_me);	// Constructor
        Vector::~Vector();		// Destructor

        double calc_angle(double x, double y);
        void aim(double x, double y);
        void aim(Vector *target);
        void update_location(void);
        void set_from_screen_coords(double screen_x, double screen_y, Uint32 screen_width, Uint32 screen_height);
        void set_from(Vector *v);
        void bounds_check(Vector *size);
        void accelerate(Vector *v);
        void random_location(double x1, double y1, double x2, double y2);

        double angle,power,rotation;
        double x;
        double y;
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

double stepped_diff(double steps, double src, double dest);

#endif
