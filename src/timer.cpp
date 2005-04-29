#include "timer.hpp"

#define TIME_FRAME 30


void wait_next_frame(void){
    static Uint32 last_frame = 0;
    static Uint32 next_frame;

    if(last_frame == 0){
        last_frame = SDL_GetTicks();
    }   

    next_frame = last_frame + TIME_FRAME;
    SDL_Delay(timeLeft(next_frame));
    last_frame = next_frame;
    
/*    if((last_frame + TIME_FRAME) > now){
        last_frame += TIME_FRAME;
        printf("1\n");
    }else{
        printf("%u\n",(last_frame + TIME_FRAME - now));
        SDL_Delay(last_frame + TIME_FRAME - now);
        printf("3\n");

    }*/
    
}

Uint32 timeLeft(Uint32 nextTime)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(nextTime <= now)
        return 0;
    else
        return nextTime - now;
}


