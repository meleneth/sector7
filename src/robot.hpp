/*Stop multiple inclusion */
#ifndef ___robot_inc
#define ___robot_inc 1


#include"SDL.h"

#include"entity.hpp"

class Robot :public Entity{
    public:

        // Public data members go here.
        Robot::Robot(Uint16 mass); // Constructor
        Robot::Robot();
        Robot::~Robot(); // Destructor

        //Weapon *primary_weapon;

        virtual int chkCollision(Entity *check);

    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
