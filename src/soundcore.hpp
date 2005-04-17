#ifndef ___soundcore_inc
#define ___soundcore_inc 1

#include"SDL.h"
#include<list>
#include "soundfile.hpp"


class SoundCore {
    public:
// Public data members go here.
        SoundCore::SoundCore(void); // Constructor
        SoundCore::~SoundCore(); // Destructor
        void change_music(char *filename);
        void load_files(void);
        SoundFile *get_sound_id(sound_id sid);
        //Mix_Music *music;

        std::list<SoundFile *> sounds; 
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

extern SoundCore *soundmgr;

#endif
