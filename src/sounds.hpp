#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

using namespace sf;

class Sounds {
public:
    Sounds();
    void startSound();
    void winSound();
    void loseSound();
    void moveSound();
    void illMoveSound();
    void captureSound();
    void castleSound();
    void promoteSound();

private:
    Sound sound;
    SoundBuffer start_buf, win_buf, lose_buf;
    SoundBuffer move_buf, ill_move_buf, capture_buf;
    SoundBuffer castle_buf, promote_buf;
};

#endif /* SOUND_H */