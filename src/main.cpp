#include "Engine.h"

int main(int argc, char* argv[]) {
    Engine engine;
    if (!engine.init("Hex Map Example")) return -1;

    engine.run();
    engine.clean();
    return 0;
}
