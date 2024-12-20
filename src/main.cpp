#include "game.hpp"

int main() {
    Game* chessmaster = new Game();
    chessmaster->play();
    chessmaster->~Game();

    return 0;
}