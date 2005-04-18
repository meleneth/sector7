#ifndef ___player_inc
#define ___player_inc 1

#include<deque>

#include"vector.hpp"
#include"physics.hpp"
#include"entity.hpp"
#include"weapon.hpp"
#include"w_plasmacannon.hpp"

#include"SDL.h"

class Player : public Entity {
    public:
        // Public data members go here.
        Uint16 shielded;
        Vector *cursor;
        Sint32 max_health;
        Weapon *primary_weapon;
        std::deque< Weapon* > secondary_weapons;
        Uint16 active_secondary_weapon;
        
        Sint32 xp;
        Sint32 next_level;
        Sint32 level;

        Player::Player(); // Constructor
        Player::~Player(); // Destructor

        Sint16 GetAngle(void);

        void SetAngle(Sint16 newangle);
        void MvAngle(Sint16 dir);
        void MvShip(Sint32 xdir, Sint32 ydir);
        void fire(void);
        void alt_fire(void);
        void level_up(void);
        void takeDamage(Sint32 amount);
        void add_xp(Sint32 amount);
        void add_health(Sint32 amount);
        void change_primary_weapon(Weapon *weapon);
        void add_secondary_weapon(Weapon *weapon);
        void rotate_secondary_weapon();
        
        virtual int chkCollision(Entity *check);
        virtual int chkDeath();

        virtual void has_killed(Entity *victim);
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
