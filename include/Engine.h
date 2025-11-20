#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <vector>

struct Point {
    int x, y;
};

enum class TileType { Desert, Forest, Water };

class Engine {
public:
    Engine();
    ~Engine();

    bool init(const char* title);
    void run();
    void clean();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    static const int mapWidth = 10;
    static const int mapHeight = 10;
    static const int hexSize = 40;

    std::vector<std::vector<TileType>> map;

    void generateMap();
    void renderMap();
    std::vector<Point> getHexPoints(int centerX, int centerY, int size);
    SDL_Color tileColor(TileType type);
};

#endif
