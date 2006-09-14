#ifndef ___asteroid_inc
#define ___asteroid_inc 1

#include"SDL.h"

#include"entity.hpp"


class Asteroid :public Entity{
	public:

		// Public data members go here.
		Asteroid(Uint16 mass); // Constructor
		Asteroid();
		Asteroid(Asteroid *parent, Uint16 mass);
		~Asteroid(); // Destructor

        void setup_asteroid(void);

		virtual int chkCollision(Entity *check);

        virtual void death(void);

	private:
		// Private members go here.

	protected:
		// Protected members go here.
};

#endif
