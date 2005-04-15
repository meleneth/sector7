#ifndef ___b_minerbotevent_inc
#define ___b_minerbotevent_inc 1

#include"SDL.h"

#include"event.hpp"
#include"b_minerbot.hpp"

enum MinerEvent { ME_FIRE, ME_CLAWSTAB, ME_CLAWRETURN, ME_CLAWIDLE };

class MinerBotEvent: public Event  {
    public:
// Public data members go here.
        MinerBotEvent::MinerBotEvent(MinerEvent type, int time_index, MinerBot *bot, bool repeats); // Constructor
        MinerBotEvent::~MinerBotEvent(); // Destructor
        virtual void run(void);

        virtual Event *clone(void);
    private:
        // Private members go here.
    MinerEvent type;
    MinerBot *miner;
    protected:
        // Protected members go here.
};

#endif
