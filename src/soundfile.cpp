#include "stdutil.hpp"
#include "soundfile.hpp"


// Public data members go here.
SoundFile::SoundFile(sound_id id, char *filename) // Constructor
{
    sid=id;
    sound=Mix_LoadWAV(filename);
    channel=-1;
}

SoundFile::~SoundFile() // Destructor
{
}

void SoundFile::play(void)
{
    if(channel != -1){
        stop();
    }
    channel=Mix_PlayChannel(-1, sound, -1);
}

void SoundFile::stop(void)
{
    Mix_HaltChannel(channel);
}

// Private members go here.

// Protected members go here.
