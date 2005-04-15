#ifndef __engine_inc
#define __engine_inc 1

#include "renderer.hpp"
#include "player.hpp"
#include "console.hpp"
#include "particles.hpp"
#include "entitymgr.hpp"
#include "entity.hpp"
#include "scoreboard.hpp"
#include"game.hpp"

extern Player *player1;
extern Console *sysconsole;
extern char *servername;
extern Uint32 quit;
extern EntityMgr *bg_particles;
extern EntityMgr *fg_particles;
extern ScoreBoard *scoreboard;
extern Sint32 numroids;
extern Game *game;

#endif
