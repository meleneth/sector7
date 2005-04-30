#ifndef ___camera_inc
#define ___camera_inc 1

#include"SDL.h"
#include"sector.hpp"
#include"area.hpp"

class Camera : public Sector {
    public:
        // Public data members go here.
        Camera::Camera(std::string camera_id); // Constructor
        Camera::~Camera(); // Destructor
        void follow(Entity *bird, Area *roam);

    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
