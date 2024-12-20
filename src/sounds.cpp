#include "sounds.hpp"

Sounds::Sounds() {
    start_buf.loadFromFile("./sounds/start.wav");
    win_buf.loadFromFile("./sounds/win.wav");
    lose_buf.loadFromFile("./sounds/lose.wav");
    move_buf.loadFromFile("./sounds/move.wav");
    ill_move_buf.loadFromFile("./sounds/illmove.wav");
    capture_buf.loadFromFile("./sounds/capture.wav");
    castle_buf.loadFromFile("./sounds/castle.wav");
    promote_buf.loadFromFile("./sounds/promote.wav");
}

void Sounds::startSound() {
    sound.setBuffer(start_buf);
    sound.play();
}
    
void Sounds::winSound() {
    sound.setBuffer(win_buf);
    sound.play();
}

void Sounds::loseSound() {
    sound.setBuffer(lose_buf);
    sound.play();
}

void Sounds::moveSound() {
    sound.setBuffer(move_buf);
    sound.play();
}

void Sounds::illMoveSound() {
    sound.setBuffer(ill_move_buf);
    sound.play();
}

void Sounds::captureSound() {
    sound.setBuffer(capture_buf);
    sound.play();
}

void Sounds::castleSound() {
    sound.setBuffer(castle_buf);
    sound.play();
}

void Sounds::promoteSound() {
    sound.setBuffer(promote_buf);
    sound.play();
}