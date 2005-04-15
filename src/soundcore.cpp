#include"SDL_mixer.h"

#include "stdutil.hpp"
#include "soundcore.hpp"



// Public data members go here.
SoundCore::SoundCore(void) // Constructor
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(2);
    }
    load_files();

    Mix_PlayMusic(music, 0);
}

SoundCore::~SoundCore() // Destructor
{
}

void SoundCore::change_music(char *filename)
{
}

void SoundCore::load_files(void)
{
    sounds.push_front(new SoundFile(SHOT_FIRE, "../sounds/fire.wav"));
    sounds.push_front(new SoundFile(SHOT_HIT, "../sounds/hit.wav"));
    sounds.push_front(new SoundFile(POWERUP, "../sounds/powerup.wav"));
    sounds.push_front(new SoundFile(SHOT_DESTROYED, "../sounds/destroy.wav"));

    music = Mix_LoadMUS("../sounds/music.mp3");
}

SoundFile *SoundCore::get_sound_id(sound_id sid)
{
    std::list < SoundFile * >::iterator i;
    for(i = sounds.begin(); i != sounds.end(); ++i){
        if((*i)->sid == sid) return *i;
    }
}


// Private members go here.

// Protected members go here.
