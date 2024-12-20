#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

class Stockfish {
public:
    Stockfish();
    ~Stockfish();
    std::string getBestmove(const std::string& route, int ms = 500);

private:
    pid_t pid;
    FILE* to_stream;
    FILE* from_stream;
    int to_pipe[2], from_pipe[2];
};

#endif /* ENGINE_H */