#include "pieces.hpp"

// King
bool King::isValid(Vector2f prev, Vector2f next, Sprite* coords) {
    if(abs(next.x - prev.x) > STEP || abs(next.y - prev.y) > STEP)
        return false;
    return moved = true;
}


// Queen
bool Queen::isValid(Vector2f prev, Vector2f next, Sprite* coords) {
    if(next.x != prev.x && next.y != prev.y && abs(next.x - prev.x) != abs(next.y - prev.y))
        return false;

    between_pos = next - prev;
    if(next.x == prev.x)
        return verticalYMove(prev, next, coords);
    else if(next.y == prev.y)
        return verticalXMove(prev, next, coords);
    return diagonalMove(prev, next, coords);
}

bool Queen::betweenNextPrev(Vector2f prev, Vector2f next, Sprite* coords, float dx, float dy) {
    for(int i=0; i<32; i++)
        for(int j=1; j<range; j++)
            if(coords[i].getPosition() == prev + Vector2f(j*dx, j*dy))
                return false;
    return moved = true;
}

bool Queen::verticalYMove(Vector2f prev, Vector2f next, Sprite* coords) {
    range = abs(between_pos.y) / STEP;
    if(between_pos.y > 0)
        return betweenNextPrev(prev, next, coords, 0, STEP);
    else
        return betweenNextPrev(prev, next, coords, 0, -STEP);
}

bool Queen::verticalXMove(Vector2f prev, Vector2f next, Sprite* coords) {
    range = abs(between_pos.x) / STEP;
    if(between_pos.x > 0)
        return betweenNextPrev(prev, next, coords, STEP, 0);
    else
        return betweenNextPrev(prev, next, coords, -STEP, 0);
}

bool Queen::diagonalMove(Vector2f prev, Vector2f next, Sprite* coords) {
    range = abs(between_pos.x) / STEP;
    if(between_pos.x > 0 && between_pos.y > 0)
        return betweenNextPrev(prev, next, coords, STEP, STEP);
    else if(between_pos.x > 0 && between_pos.y < 0)
        return betweenNextPrev(prev, next, coords, STEP, -STEP);
    else if(between_pos.x < 0 && between_pos.y > 0)
        return betweenNextPrev(prev, next, coords, -STEP, STEP);
    else
        return betweenNextPrev(prev, next, coords, -STEP, -STEP);
}



// Knight
bool Knight::isValid(Vector2f prev, Vector2f next, Sprite* coords) {
    if((abs(next.x - prev.x) != 2*STEP || abs(next.y - prev.y) != STEP) &&
       (abs(next.x - prev.x) != STEP || abs(next.y - prev.y) != 2*STEP))
        return false;
    return true;
}



// Bishop
bool Bishop::isValid(Vector2f prev, Vector2f next, Sprite* coords) {
    if(abs(next.x - prev.x) != abs(next.y - prev.y))
        return false;

    between_pos = next - prev;
    return diagonalMove(prev, next, coords);
}



// Rook
bool Rook::isValid(Vector2f prev, Vector2f next, Sprite* coords) {
    if(next.x != prev.x && next.y != prev.y)
        return false;
    
    between_pos = next - prev;
    if(next.x == prev.x)
        return verticalYMove(prev, next, coords);
    else if(next.y == prev.y)
        return verticalXMove(prev, next, coords);
    return false;
}



// Pawn
bool Pawn::isValid(Vector2f prev, Vector2f next, Sprite* coords) {
    if(next.x == prev.x && prev.y - next.y == value/6*STEP) {
        for(int i=0; i<32; i++)
            if(coords[i].getPosition() == next)
                return false;
        two_step_moved = false;
        return moved = true;
    }
    
    // Two step forward
    if(!moved && next.x == prev.x && prev.y - next.y == value/3*STEP) {
        for(int i=0; i<32; i++) {
            Vector2f pos = coords[i].getPosition();
            if(pos == next + Vector2f(0, value/6*STEP) || pos == next)
                return false;
        }
        two_step_moved = true;
        return moved = true;
    }

    // Capture movement
    if(abs(next.x - prev.x) == STEP && prev.y - next.y == value/6*STEP) {
        for(int i=0; i<32; i++)
            if(coords[i].getPosition() == next) {
                two_step_moved = false;
                return moved = true;
            }
    }
    return false;
}

bool Pawn::getMoved() const {
    return two_step_moved;
}