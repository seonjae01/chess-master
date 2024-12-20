#ifndef BOARD_H
#define BOARD_H

#include "pieces.hpp"

enum VALUES {EMPTY, KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN};

class Board {
public:
    Board();
    ~Board();

    Sprite* getPieces();
    Sprite getBoardSprite();
    Sprite getPieceSprite(const int& select);
    Vector2f getPiecePos(const int& select) const;
    Pieces* getPieceInfo(const int& select) const;

    void setPiecePos(const int& select, const Vector2f& pos);
    void setPieceTex(const int& select, const int& val = 0);
    void setPieceInfo(const int& select, const int& val);

private:
    const int chess_board[8][8] = {
        -5,-4,-3,-2,-1,-3,-4,-5,
        -6,-6,-6,-6,-6,-6,-6,-6,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        6, 6, 6, 6, 6, 6, 6, 6,
        5, 4, 3, 2, 1, 3, 4, 5 };

    Pieces* piece_info[32];
    Texture pieces_tex, board_tex, promote_tex;
    Sprite board_sprite, piece_pos[32];
};

#endif /* BOARD_H */