#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>

enum class TileType {
    Desert,
    Forest,
    Water
};

struct Point {
    int x, y;
};

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
    SDL_Texture* hexBorder;   // <-- a border textúrához

    const int hexSize = 40;
    int hexWidth;
    int hexHeight;

    const int mapWidth = 20;
    const int mapHeight = 20;

    std::vector<std::vector<TileType>> map;

    void generateMap();
    void renderMap();

    std::vector<Point> getHexPoints(int cx, int cy, int size);
    SDL_Color tileColor(TileType t);
    void generateHexBorderTexture(); // <-- border generálás
};
