#include "Engine.h"
#include <cmath>
#include <iostream>
#include <ctime>

Engine::Engine()
    : window(nullptr), renderer(nullptr), hexBorder(nullptr)
{
    map.resize(mapHeight, std::vector<TileType>(mapWidth));

    hexWidth  = hexSize * 2;
    hexHeight = static_cast<int>(sqrt(3) * hexSize);
}

Engine::~Engine() {
    clean();
}

bool Engine::init(const char* title) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        0, 0,
        SDL_WINDOW_FULLSCREEN_DESKTOP
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cout << "Renderer error!\n";
        return false;
    }

    generateMap();
    generateHexBorderTexture();

    return true;
}

void Engine::generateMap() {
    srand(time(nullptr));
    for (int y = 0; y < mapHeight; y++)
        for (int x = 0; x < mapWidth; x++) {
            int r = rand() % 100;
            if (r < 50) map[y][x] = TileType::Desert;
            else if (r < 80) map[y][x] = TileType::Forest;
            else map[y][x] = TileType::Water;
        }
}

SDL_Color Engine::tileColor(TileType t) {
    switch (t) {
        case TileType::Desert: return {237, 201, 175, 255};
        case TileType::Forest: return {34, 139, 34, 255};
        case TileType::Water:  return {30, 144, 255, 255};
    }
    return {0, 0, 0, 255};
}

std::vector<Point> Engine::getHexPoints(int cx, int cy, int size) {
    std::vector<Point> pts(6);

    for (int i = 0; i < 6; i++) {
        double angle = M_PI / 180.0 * (60 * i); // FLAT TOP
        pts[i].x = cx + (int)(size * cos(angle));
        pts[i].y = cy + (int)(size * sin(angle));
    }

    return pts;
}

void Engine::generateHexBorderTexture() {
    hexBorder = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        hexWidth,
        hexHeight
    );

    SDL_SetTextureBlendMode(hexBorder, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, hexBorder);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    auto pts = getHexPoints(hexWidth / 2, hexHeight / 2, hexSize);

    for (int i = 0; i < 6; i++) {
        int j = (i + 1) % 6;
        SDL_RenderDrawLine(renderer, pts[i].x, pts[i].y, pts[j].x, pts[j].y);
    }

    SDL_SetRenderTarget(renderer, NULL);
}

void Engine::renderMap() {
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {

            int cx = x * (hexWidth * 0.75) + hexSize;
            int cy = y * hexHeight + (x % 2) * (hexHeight / 2) + hexSize;

            std::vector<Point> pts = getHexPoints(cx, cy, hexSize);

            Sint16 vx[6], vy[6];
            for (int i = 0; i < 6; i++) {
                vx[i] = pts[i].x;
                vy[i] = pts[i].y;
            }

            SDL_Color c = tileColor(map[y][x]);
            filledPolygonRGBA(renderer, vx, vy, 6, c.r, c.g, c.b, 255);

            SDL_Rect r = {
                cx - hexWidth / 2,
                cy - hexHeight / 2,
                hexWidth,
                hexHeight
            };

            SDL_RenderCopy(renderer, hexBorder, NULL, &r);
        }
    }
}

void Engine::run() {
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderMap();

        SDL_RenderPresent(renderer);
    }
}

void Engine::clean() {
    if (hexBorder) SDL_DestroyTexture(hexBorder);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
