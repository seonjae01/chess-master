#ifndef PIECES_H
#define PIECES_H
#define STEP 100

#include <SFML/Graphics.hpp>

using namespace sf;


class Pieces {
public:
    Pieces(int val) : value(val) {};
    virtual ~Pieces() = default;
    virtual bool isValid(Vector2f prev, Vector2f next, Sprite* coords) = 0;
    
    virtual bool getMoved() const { return moved; }
    int getValue() const { return value; }

protected:
    bool moved = false;
    int range, value;
    Vector2f between_pos;
};



class King : public Pieces {
public:
    King(int val) : Pieces(val) {}
    bool isValid(Vector2f prev, Vector2f next, Sprite* coords);
};



class Queen : public Pieces {
public:
    Queen(int val) : Pieces(val) {}
    bool isValid(Vector2f prev, Vector2f next, Sprite* coords) override;

    bool betweenNextPrev(Vector2f prev, Vector2f next, Sprite* coords, float dx, float dy);
    bool verticalYMove(Vector2f prev, Vector2f next, Sprite* coords);
    bool verticalXMove(Vector2f prev, Vector2f next, Sprite* coords);
    bool diagonalMove(Vector2f prev, Vector2f next, Sprite* coords);
};



class Knight : public Pieces {
public:
    Knight(int val) : Pieces(val) {}
    bool isValid(Vector2f prev, Vector2f next, Sprite* coords) override;
};



class Bishop : public Queen {
public:
    Bishop(int val) : Queen(val) {}
    bool isValid(Vector2f prev, Vector2f next, Sprite* coords) override;
};



class Rook : public Queen {
public:
    Rook(int val) : Queen(val) {}
    bool isValid(Vector2f prev, Vector2f next, Sprite* coords) override;
};



class Pawn : public Pieces {
public:
    Pawn(int val) : Pieces(val) {}
    bool isValid(Vector2f prev, Vector2f next, Sprite* coords) override;
    bool getMoved() const;

private:
    bool two_step_moved = false;
};

#endif /* PIECES_H */