#ifndef __engine_inc
#define __engine_inc 1

#include "renderer.hpp"
#include "console.hpp"
#include "particles.hpp"
#include "entitymgr.hpp"
#include "entity.hpp"

extern Console *sysconsole;
extern char *servername;
extern Uint32 quit;
extern EntityMgr *bg_particles;
extern EntityMgr *fg_particles;
extern Sint32 numroids;

#endif
