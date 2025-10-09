g++ $(find src -name "*.cpp") -o engine -Iinclude $(sdl2-config --cflags --libs) -Wall -Wextra -g
#g++ $(find src -name "*.cpp") -o engine.exe -Iinclude $(sdl2-config --cflags --libs) -Wall -Wextra -g