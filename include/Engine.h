#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>

class Engine {
public:
    Engine();
    ~Engine();

    bool init(const char* title, int width, int height);
    void run();
    void clean();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
};

#endif // ENGINE_H
