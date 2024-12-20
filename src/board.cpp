#include "board.hpp"

Board::Board() {
    pieces_tex.loadFromFile("./images/pieces.png");
    board_tex.loadFromFile("./images/board.png");
    board_sprite.setTexture(board_tex);

    int seq = 0;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(chess_board[i][j] == 0)
                continue;
            
            int value = chess_board[i][j];
            int x = abs(value) - 1;
            int y = value<0?1:0;
            
            piece_pos[seq].setTextureRect(IntRect(x*STEP, y*STEP, STEP, STEP));
            piece_pos[seq].setPosition(j*STEP, i*STEP);
            piece_pos[seq].setTexture(pieces_tex);
            
            if(abs(value) == KING) piece_info[seq] = new King(value);
            else if(abs(value) == QUEEN) piece_info[seq] = new Queen(value);
            else if(abs(value) == BISHOP) piece_info[seq] = new Bishop(value);
            else if(abs(value) == KNIGHT) piece_info[seq] = new Knight(value);
            else if(abs(value) == ROOK) piece_info[seq] = new Rook(value);
            else if(abs(value) == PAWN) piece_info[seq] = new Pawn(value);
            seq++;
        }
    }
}

Board::~Board() {
    for(int i=0; i<32; i++)
        delete piece_info[i];
}

Sprite* Board::getPieces() {
    return piece_pos;
}

Sprite Board::getBoardSprite() {
    return board_sprite;
}

Sprite Board::getPieceSprite(const int& select) {
    return piece_pos[select];
}

Vector2f Board::getPiecePos(const int& select) const {
    return piece_pos[select].getPosition();
}

Pieces* Board::getPieceInfo(const int& select) const {
    return piece_info[select];
}

void Board::setPiecePos(const int& select, const Vector2f& pos) {
    piece_pos[select].setPosition(pos);
}

void Board::setPieceTex(const int& select, const int& val) {
    if(val) {
        piece_pos[select].setTextureRect(IntRect((abs(val) - 1)*STEP, (val<0?1:0)*STEP, STEP, STEP));
        piece_pos[select].setTexture(pieces_tex);
    }
    else {
        promote_tex.loadFromFile("./images/white_prom.png");
        piece_pos[select].setTextureRect(IntRect(0, 0, STEP, STEP));
        piece_pos[select].setTexture(promote_tex);
    }
}

void Board::setPieceInfo(const int& select, const int& val) {
    delete piece_info[select];
    if(abs(val) == QUEEN) piece_info[select] = new Queen(val);
    else if(abs(val) == BISHOP) piece_info[select] = new Bishop(val);
    else if(abs(val) == KNIGHT) piece_info[select] = new Knight(val);
    else if(abs(val) == ROOK) piece_info[select] = new Rook(val);
}