#include "Engine.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

Engine::Engine() : window(nullptr), renderer(nullptr), isRunning(false) {
    map.resize(mapHeight, std::vector<TileType>(mapWidth));
}

Engine::~Engine() {
    clean();
}

bool Engine::init(const char* title) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    isRunning = true;
    generateMap();
    return true;
}

void Engine::generateMap() {
    srand((unsigned int)time(nullptr));
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int r = rand() % 100;
            if (r < 50) map[y][x] = TileType::Desert;
            else if (r < 80) map[y][x] = TileType::Forest;
            else map[y][x] = TileType::Water;
        }
    }
}

std::vector<Point> Engine::getHexPoints(int centerX, int centerY, int size) {
    std::vector<Point> points;
    for (int i = 0; i < 6; ++i) {
        double angle_deg = 60 * i - 30;
        double angle_rad = M_PI / 180.0 * angle_deg;
        int x = centerX + static_cast<int>(size * cos(angle_rad));
        int y = centerY + static_cast<int>(size * sin(angle_rad));
        points.push_back({x, y});
    }
    return points;
}

SDL_Color Engine::tileColor(TileType type) {
    switch (type) {
        case TileType::Desert: return {237, 201, 175, 255};
        case TileType::Forest: return {34, 139, 34, 255};
        case TileType::Water:  return {30, 144, 255, 255};
    }
    return {0, 0, 0, 255};
}

void Engine::renderMap() {
    int w = hexSize * 2;
    int h = static_cast<int>(sqrt(3) * hexSize);

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int centerX = x * (3 * hexSize / 2) + hexSize;
            int centerY = y * h + (x % 2) * (h / 2) + hexSize;

            std::vector<Point> hexPoints = getHexPoints(centerX, centerY, hexSize);

            SDL_Color c = tileColor(map[y][x]);
            SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);

            for (int i = 0; i < 6; ++i) {
                Point p1 = hexPoints[i];
                Point p2 = hexPoints[(i + 1) % 6];
                SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
            }
        }
    }
}

void Engine::run() {
    SDL_Event event;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isRunning = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderMap();

        SDL_RenderPresent(renderer);
    }
}

void Engine::clean() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
