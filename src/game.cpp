#include "game.hpp"

Game::Game() {
    window.create(VideoMode(800, 800), "Chess Master");
    window.setMouseCursorGrabbed(true);

    board = new Board();
    sounds = new Sounds();
    engine = new Stockfish();
}

Game::~Game() {
    delete board;
    delete sounds;
    delete engine;
}

string Game::coordToStr(const Vector2f& coord) {
    string route = "";
    route += char(coord.x/STEP+97);
    route += char(7-coord.y/STEP+49);
    return route;
}

Vector2f Game::strToCoord(const char& a, const char& b) {
    int x = int(a) - 97;
    int y = 7-int(b)+49;
    return Vector2f(x*STEP,y*STEP);
}

bool Game::castling(const int& pick, const Vector2f& prev, const Vector2f& next) {
    if(next.y != prev.y || abs(next.x - prev.x) != 2*STEP)
        return false;
    
    if(check || board->getPieceInfo(pick)->getMoved())
        return false;
    
    int val = board->getPieceInfo(pick)->getValue();

    // Queen side Castling
    if(next == Vector2f(2*STEP, next.y)) {
        val = (val < 0) ? 0 : 24;
        if(board->getPieceInfo(val)->getMoved())
            return false;
        
        for(int i=0; i<32; i++) {
            Vector2f chk = board->getPiecePos(i);
            if(chk == Vector2f(STEP, next.y) ||
               chk == Vector2f(2*STEP, next.y) ||
               chk == Vector2f(3*STEP, next.y))
                return false;
        }
        board->setPiecePos(val, Vector2f(3*STEP, next.y));
    }
    // King side Castling
    else if(next == Vector2f(6*STEP, next.y)) {
        val = (val < 0) ? 7 : 31;
        if(board->getPieceInfo(val)->getMoved())
            return false;

        for(int i=0; i<32; i++) {
            Vector2f chk = board->getPiecePos(i);
            if(chk == Vector2f(5*STEP, next.y) ||
               chk == Vector2f(6*STEP, next.y))
                return false;
        }
        board->setPiecePos(val, Vector2f(5*STEP, next.y));
    }

    sounds->castleSound();
    return true;
}

bool Game::enpassant(const int& pick, const Vector2f& prev, const Vector2f& next) {
    int val = board->getPieceInfo(pick)->getValue();
    if(abs(next.x - prev.x) == STEP && prev.y - next.y == val/6*STEP) {
        Vector2f chk = next + Vector2f(0, val/6*STEP);
        for(int i=0; i<32; i++) {
            if(board->getPiecePos(i) == next)
                return false;
            if(board->getPiecePos(i) == chk && abs(board->getPieceInfo(i)->getValue()) == PAWN && 
               prev_pawn != Vector2f(-STEP, -STEP) && board->getPieceInfo(i)->getValue() * val < 0) {
                board->setPiecePos(i, Vector2f(-100, -100));
                sounds->moveSound();
                return true;
            }
        }
    }
    return false;
}

void Game::promotion(const int& pick, const Vector2i& mouse, const Vector2f& next) {
    int val = 0;
    if(IntRect(next.x+STEP/2, STEP/2, STEP/2, STEP/2).contains(mouse)) { val = ROOK; path += "r"; }
    else if(IntRect(next.x, STEP/2, STEP/2, STEP/2).contains(mouse)) { val = KNIGHT; path += "k"; }
    else if(IntRect(next.x+STEP/2, 0, STEP/2, STEP/2).contains(mouse)) { val = BISHOP; path += "b"; }
    else if(IntRect(next.x, 0, STEP/2, STEP/2).contains(mouse)) { val = QUEEN; path += "q"; }
    
    is_promotion = (!val) ? true : false;
    if(!is_promotion) {
        board->setPieceInfo(pick, val);
        board->setPieceTex(pick, val);
        sounds->promoteSound();
        aimove();
    }
}

bool Game::move(const int& pick, const Vector2f& prev, const Vector2f& next) {
    bool moved = false;
    int val = board->getPieceInfo(pick)->getValue();

    // Castling movement
    if(abs(val) == KING)
        moved = castling(pick, prev, next);

    // En passant movement
    if(abs(val) == PAWN)
        moved = enpassant(pick, prev, next);

    // Normal movement
    if(!moved && board->getPieceInfo(pick)->isValid(prev, next, board->getPieces()))
        moved = capture(pick, next);
    
    // Check correct movement & Check pawn moves two forward whether en passant is possible
    if(moved) {
        board->setPiecePos(pick, next);
        prev_pawn = (abs(val) == PAWN && board->getPieceInfo(pick)->getMoved()) ? next : Vector2f(-STEP, -STEP);
    }
    else {
        board->setPiecePos(pick, prev);
        sounds->illMoveSound();
    }

    // Check promotion
    if(val == PAWN && board->getPiecePos(pick) == Vector2f(next.x, 0)) {
        board->setPieceTex(pick);
        is_promotion = true;
    }
    return moved;
}

bool Game::capture(const int& pick, const Vector2f& next) {
    int val = board->getPieceInfo(pick)->getValue();
    for(int i=0; i<32; i++) {
        if(board->getPiecePos(i) == next) {
            if(board->getPieceInfo(i)->getValue() * val > 0) return false;
            board->setPiecePos(i, Vector2f(-STEP, -STEP));
            sounds->captureSound();
            return true;
        }
    }
    sounds->moveSound();
    return true;
}

bool Game::isCheck() {
    Vector2f king_pos = board->getPiecePos(28);
    for(int i=0; i<16; i++) {
        Vector2f prev = board->getPiecePos(i);
        if(board->getPieceInfo(i)->isValid(prev, king_pos, board->getPieces()))
            return true;
    }
    return false;
}

void Game::rendering() {
    window.clear();
    window.draw(board->getBoardSprite());
    
    for(int i=0; i<32; i++)
        window.draw(board->getPieceSprite(i));
    window.display();
}

void Game::aimove() {
    record += (path + " ");
    string line = engine->getBestmove(record);
    string aipath = line.substr(9, (line[13] == ' ' || line[13] == '\n') ? 4 : 5);
    record += (aipath + " ");
    
    prev_pos = strToCoord(aipath[0], aipath[1]);
    next_pos = strToCoord(aipath[2], aipath[3]);

    int pick;
    for(int i=0; i<16; i++) {
        if(board->getPiecePos(i) == prev_pos && move(i, prev_pos, next_pos)) {
            pick = i;
            break;
        }
    }

    if(aipath.length() == 5) {
        int val;
        if(aipath[4] == 'q') val = QUEEN;
        else if(aipath[4] == 'b') val = BISHOP;
        else if(aipath[4] == 'k') val = KNIGHT;
        else if(aipath[4] == 'r') val = ROOK;
        board->setPieceInfo(pick, -val);
        board->setPieceTex(pick, -val);
    }
    
    rendering();
    if(line.length() == 13 || line.length() == 14)
        result(2);
}

void Game::play() {
    sounds->startSound();
    while(window.isOpen()) {
        mouse_pos = Mouse::getPosition(window);

        while(window.pollEvent(event)) {
            if(event.type == Event::KeyPressed) {
                // Press "ESC" or "Q" to exit
                if(event.key.code == Keyboard::Escape || event.key.code == Keyboard::Q)
                    window.close();
                
                // Press "R" to restart game
                if(event.key.code == Keyboard::R)
                    restart();
            }
            
            // Mouse click
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if(is_promotion) {
                    promotion(select, mouse_pos, next_pos);
                    continue;
                }

                for(int i=0; i<32; i++) {
                    if(board->getPieceSprite(i).getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                        dragging = true, select = i;
                        diff = Vector2f(mouse_pos) - board->getPiecePos(select);
                        prev_pos = board->getPiecePos(select);
                    }
                }
            }

            // Drop
            if(dragging && event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                dragging = false;
                Vector2f adj_pos = board->getPiecePos(select) + Vector2f(STEP/2, STEP/2);
                next_pos = Vector2f(STEP * int(adj_pos.x / STEP), STEP * int(adj_pos.y / STEP));
                
                // Modify if beyond board
                if(prev_pos == next_pos || next_pos.x < 0 || next_pos.x > 700 || next_pos.y < 0 || next_pos.y > 700) {
                    board->setPiecePos(select, prev_pos);
                    continue;
                }

                // Move player's piece & Move AI's piece
                if(move(select, prev_pos, next_pos)) {
                    path = coordToStr(prev_pos) + coordToStr(next_pos);
                    rendering();
                    if(is_promotion) continue;
                    aimove();
                    check = isCheck();
                }
            }
        }

        // Drag
        if(dragging)
            board->setPiecePos(select, Vector2f(mouse_pos) - diff);
        rendering();
    }
}

void Game::restart() {
    delete board;
    delete sounds;
    delete engine;

    board = new Board();
    sounds = new Sounds();
    engine = new Stockfish();

    dragging = false;
    is_promotion = false;
    select = -1;
    record = "";
    sounds->startSound();
}

void Game::result(int res) {
    Font font;
    font.loadFromFile("./fonts/ChunkFive-Regular.otf");
    Text text("", font, STEP);
    text.setFillColor(Color::Black);

    if(res == 1) {
        text.setString("CHECKMATE!");
        text.setPosition(53, 336);
        sounds->winSound();
    }
    else if(res == 2) {
        text.setString("GAME OVER");
        text.setPosition(72, 336);
        sounds->loseSound();
    }
    
    window.draw(text);
    window.display();
    sleep(5);
    restart();
}