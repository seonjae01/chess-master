#include "engine.hpp"

Stockfish::Stockfish() {
    if(pipe(to_pipe) == -1 || pipe(from_pipe) == -1)
        throw runtime_error("Failed to create pipes.");

    pid = fork();
    if(pid == 0) {
        close(to_pipe[1]);
        close(from_pipe[0]);
        dup2(to_pipe[0], STDIN_FILENO);
        dup2(from_pipe[1], STDOUT_FILENO);
        execl("./stockfish", "stockfish");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0) {
        close(to_pipe[0]);
        close(from_pipe[1]);
        to_stream = fdopen(to_pipe[1], "w");
        from_stream = fdopen(from_pipe[0], "r");

        string commands[] = {
            "uci\n",
            "isready\n",
            "ucinewgame\n",
            "setoption name Threads value 4\n"
        };

        for(const auto& cmd : commands) {
            fputs(cmd.c_str(), to_stream);
            fflush(to_stream);
        }
    }
    else throw runtime_error("Failed to fork.");
}

Stockfish::~Stockfish() {
    fputs("quit\n", to_stream);
    fflush(to_stream);
    fclose(to_stream);
    fclose(from_stream);
    kill(pid, SIGTERM);
    waitpid(pid, nullptr, 0);
}

string Stockfish::getBestmove(const string& route, int ms) {
    fputs(("position startpos moves " + route + "\n").c_str(), to_stream);
    fputs(("go movetime " + to_string(ms) + "\n").c_str(), to_stream);
    fflush(to_stream);

    char buffer[256];
    while(fgets(buffer, sizeof(buffer), from_stream) != nullptr) {
        if(!strncmp(buffer, "bestmove", 8)) break;
    }
    return buffer;
}
