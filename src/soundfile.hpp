#ifndef ___soundfile_inc
#define ___soundfile_inc 1

#include"sounds.hpp"

#include"SDL.h"
#include"SDL_mixer.h"

class SoundFile {
    public:
// Public data members go here.
        SoundFile::SoundFile(sound_id id, char *filename); // Constructor
        SoundFile::~SoundFile(); // Destructor
        void play(void);
        void stop(void);

        sound_id sid;
        Mix_Chunk *sound;
        int channel;
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
