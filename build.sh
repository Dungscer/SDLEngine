mkdir build
cd build

sudo apt update
sudo apt install cmake

cmake ..
make
./SDLEngine