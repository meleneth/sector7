#include "timer.hpp"

#define TIME_FRAME 30

void wait_next_frame(void){
    static Uint32 last_frame = 0;
    Uint32 now = SDL_GetTicks();

    if(last_frame == 0)
    {
        last_frame = SDL_GetTicks();
    }

    if((last_frame + TIME_FRAME) > now){
        last_frame += TIME_FRAME;
    }else{
        SDL_Delay(last_frame + TIME_FRAME - now);
    }
    
}


