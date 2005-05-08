#ifndef ___camera_inc
#define ___camera_inc 1

#include"SDL.h"
#include"sector.hpp"
#include"area.hpp"

class Camera : public Sector {
    public:
        // Public data members go here.
        Camera::Camera(std::string camera_id, Uint32 xres, Uint32 yres); // Constructor
        Camera::~Camera(); // Destructor
        virtual void render(void);
        void follow(Entity *bird);
        void set_from_screen_coords(Vector *v, double screen_x, double screen_y);
    
        Area *visible_area;
        Area *inner_bound;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
