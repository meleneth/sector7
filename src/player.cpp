#include "stdutil.hpp"
#include<math.h>

#include"player.hpp"
#include"renderer.hpp"
#include"entitymgr.hpp"
#include"engine.hpp"


#include"renderer.hpp"
#include"entitymgr.hpp"
#include"texture.hpp"

// Public data members go here.
Player::Player(): Entity(E_PLAYER)			// Constructor
{
    v->set_from_screen_coords(HALFXRES, YRES - 100);
    v->power = 0;

    rotation = 180;

    xp = 0;
    next_level = 400;
    level=1;
    
    accelerating = false;
    size=16;
    v->power =0;
    shielded=false;
    max_health=256;
    health = max_health;
    texture= get_tex_id(TILE_SHIP);
    cursor = new Vector();
    primary_weapon =  new PlasmaCannon(this);
    add_secondary_weapon(new PlasmaCannon(this));
}

Player::~Player()			// Destructor
{
    delete cursor;
    delete primary_weapon;
}

void Player::change_primary_weapon(Weapon *weapon)
{
    delete primary_weapon;
    primary_weapon = weapon;
}

void Player::add_secondary_weapon(Weapon *weapon)
{
    secondary_weapons.push_front(weapon);
    active_secondary_weapon = 0;
}

void Player::MvShip(Sint32 xdir, Sint32 ydir)
{
    v->x+=xdir;
    v->y+=ydir;
}

void Player::MvAngle(Sint16 dir)
{
    double temp = v->angle;

    temp += dir;
    if (temp < 0)
        temp += 360;
    if (temp > 360)
        temp -= 360;
    v->angle = temp;
}

void Player::fire(void)
{
    primary_weapon->fire_shot(v->x, v->y - 30);    
}

void Player::alt_fire(void)
{
    secondary_weapons[active_secondary_weapon]->fire_shot(cursor->x, cursor->y);    
}

void Player::takeDamage(Sint32 amount)
{
	if(shielded){
        printf("Thunk! Shields hit!\n");
		shielded = false;
		texture = get_tex_id(TILE_SHIP);
		return;
	}
    printf("Bang0r!! took %d damage!\n", amount);
    health -= amount;
}

int Player::chkCollision(Entity *check)
{
    int result;

    result = Entity::chkCollision(check);


    if(result){
        if(check->alignment && E_ENEMY) {
            // it did damage to us, now it's our turn
            check->takeDamage(50);
        }
    }
    return result;
}

void Player::add_xp(Sint32 amount)
{
    xp += amount;
    if(xp > next_level){
        level_up();
    }
}

void Player::level_up()
{
    printf("OMFG!! Level UP!@!#\n\n Welcome to level %d\n\n", ++level);
    next_level = (Sint32)m_round(next_level * 1.2);
    max_health = (Sint32)(max_health * 1.5);
    health = max_health;;
}

void Player::add_health(Sint32 amount)
{
    health = health + amount > max_health ? max_health : health + amount;
}
// Private members go here.

void Player::has_killed(Entity *victim)
{
    add_xp(victim->experiance_value);
}

int Player::chkDeath()
{
    return false;
}

void Player::rotate_secondary_weapon() {
    active_secondary_weapon = ++active_secondary_weapon % secondary_weapons.size();
}
// Protected members go here.
