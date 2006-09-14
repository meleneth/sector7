/*Stop multiple inclusion */
#ifndef ___vector_inc
#define ___vector_inc 1

#include"SDL.h"
#include"types.hpp"
#include"area.hpp"
class Area;
class Vector {
    public:
        // Public data members go here.
        Vector();	// Constructor
        Vector(Vector *copy_me);	// Constructor
        ~Vector();		// Destructor

        double calc_angle(double x, double y);
        double calc_angle(Vector *target);
        double distance(Vector *target);

        void aim(double x, double y);
        void aim(Vector *target);
        void update_location(void);
        void set_from(Vector *v);
        void bounds_check(Area *boundary);
        void accelerate(Vector *v);
        void follow(Vector *v, double leash_length);
        void random_location(double x1, double y1, double x2, double y2);
        Vector *difference(Vector *p);

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
