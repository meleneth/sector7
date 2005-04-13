/*Stop multiple inclusion */
#ifndef ___entity_inc
#define ___entity_inc 1

#include"SDL.h"
#include"texture.hpp"
#include"vector.hpp"
#include"ent_squad.hpp"

#define E_PLAYER 1
#define E_ENEMY 2
#define E_NEUTRAL 4
#define E_POWERUP 8
#define E_LANDSCAPE 16

#define ENT_ALIGNMENT Sint16

enum ENT_TYPE { ENT_ASTEROID, ENT_WEP_POWERUP, ENT_SHLD_POWERUP, ENT_PLAYER, ENT_PLAYERSHOT, ENT_TITLESCREEN, ENT_ROBOT };

#define ENTID_TYPE Uint32

class EntSquad;

class Entity {
    public:
        ENTID_TYPE ent_id;
        ENT_ALIGNMENT alignment;
        int collision_mask;

        Sint32 health;
        RESTYPE rotation;
        Uint16 experiance_value;
        Uint16 score_value;
        Texture *texture;
        Uint16 accelerating;
        Uint8 size; // 1/2 value always.. gl :)
        int taken_damage;
        Vector *v;
        EntSquad *squad;

        // Public data members go here.
        Entity::Entity(); // Constructor
        Entity::Entity(ENT_ALIGNMENT ent_type); // Constructor

        void setup_entity(void);
        void add_timed_event(int time_offset, void *function, Entity *who_is_acting);
        virtual Entity::~Entity(); // Destructor

        virtual int frameupdate(void);

        virtual void update_location(void);
        virtual void render(void);

        virtual int chkDeath(void);
        virtual int chkCollision(Entity *checkme);

        virtual void has_killed(Entity *victim);

        virtual int takeDamage(Sint16 dmg);
        virtual int takeDamage(Sint16 dmg, Entity *who_was_holding_the_gun);
        virtual void death();
        void kill_me_now(void); 

    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
