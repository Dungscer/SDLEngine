#include "Engine.h"

int main(int argc, char* argv[]) {
    Engine engine;

    if (!engine.init("Window", 800, 600)) {
        return -1;
    }

    engine.run();
    engine.clean();

    return 0;
}
