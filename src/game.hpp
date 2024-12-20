#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "sounds.hpp"
#include "engine.hpp"

class Game {
public:
    Game();
    ~Game();

    string coordToStr(const Vector2f& coord);
    Vector2f strToCoord(const char& a, const char& b);

    bool castling(const int& pick, const Vector2f& prev, const Vector2f& next);
    bool enpassant(const int& pick, const Vector2f& prev, const Vector2f& next);
    void promotion(const int& pick, const Vector2i& mouse, const Vector2f& next);

    bool move(const int& pick, const Vector2f& prev, const Vector2f& next);
    bool capture(const int& pick, const Vector2f& next);
    
    bool isCheck();
    void rendering();
    void aimove();
    void play();
    void restart();
    void result(int res);

private:
    bool check = false;
    bool dragging = false;
    bool is_promotion = false;
    int select;

    string record, path;    
    RenderWindow window;
    Event event;

    Vector2i mouse_pos;
    Vector2f prev_pos, next_pos;
    Vector2f prev_pawn, diff;

    Board* board;
    Sounds* sounds;
    Stockfish* engine;
};

#endif /* GAME_H */