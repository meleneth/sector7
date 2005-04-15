#include "stdutil.hpp"
#include "b_minerbotevent.hpp"
#include "b_minerbot.hpp"
#include"engine.hpp"


// Public data members go here.
MinerBotEvent::MinerBotEvent(MinerEvent e_type, int time_index, MinerBot *bot, bool repeats):Event(time_index, bot->head, repeats) // Constructor
{
    this->time_index = time_index;
    this->repeats = repeats;
    type = e_type;
    miner = bot;
    time_offset = game->framecount;
}

MinerBotEvent::~MinerBotEvent() // Destructor
{
}

Event *MinerBotEvent::clone(void)
{
    return new MinerBotEvent(type, time_index, miner, repeats);
}

void MinerBotEvent::run(void)
{
    switch(type){
        case ME_FIRE:
                break;
        case ME_CLAWSTAB:
            miner->claw_attack();
            entmgr->add_event(new MinerBotEvent(ME_CLAWRETURN, 5, miner, 0));
            break;
        case ME_CLAWIDLE:
            miner->claw_idle();
            entmgr->add_event(new MinerBotEvent(ME_CLAWSTAB, 35, miner, 0));
            break;
        case ME_CLAWRETURN:
            miner->claw_reset();
            entmgr->add_event(new MinerBotEvent(ME_CLAWIDLE, 20, miner, 0));
            break;
    };
}


// Private members go here.

// Protected members go here.
