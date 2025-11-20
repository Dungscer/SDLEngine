mkdir build
cd build

sudo apt update
sudo apt install cmake

cmake ..
make

if [ -f ./SDLEngine ]; then
    ./SDLEngine
    exit 0
fi
echo "Build not completed"
exit 1
