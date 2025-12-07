#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include<map>
#include<vector>
#include<string>
#include<iostream>

class SoundManager{
    private:
    SoundManager()=default;

    std::map<std::string, sf::SoundBuffer> buffers;
    std::vector<sf::Sound> activeSounds;
    sf::Music backgroundMusic;

    public:
    static SoundManager& get(){
        static SoundManager instance;
        return instance;
    }

    SoundManager(const SoundManager&)=delete;
    void operator=(const SoundManager&)=delete;

    //load a short sound effect call once at startup
    void loadSound(const std:: string& id, const std::string& filename){
        sf::SoundBuffer buffer;
        if(!buffer.loadFromFile(filename)){
            std::cerr<<"ERROR: Could not load sound "<<filename<<std::endl;
            return;
        }
        buffers[id]=std::move(buffer);

    }

    //play a short sound effect
    void playSound(const std::string& id, float volume=100.f){
        auto it=buffers.find(id);
        if(it==buffers.end()){
            std::cerr <<"Sound ID not found: "<<id<<std::endl;
            return;
        }

        activeSounds.emplace_back(it->second);
        activeSounds.back().setVolume(volume);
        activeSounds.back().play();
    }
    //background music
    void playMusic(const std::string& filename, bool loop=true, float volume=50.f){
        if(backgroundMusic.openFromFile(filename)){
            backgroundMusic.setLoop(loop);
            backgroundMusic.setVolume(volume);
            backgroundMusic.play();
        }
        else{
            std::cerr<<"ERROR: Could not load music "<<filename<<std::endl;
        }

    }

    void stopMusic(){
        backgroundMusic.stop();
    }

    void update()
        {
            activeSounds.erase(
                std::remove_if(activeSounds.begin(), activeSounds.end(),
                    [](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; }),
                activeSounds.end());
        }
};

#endif