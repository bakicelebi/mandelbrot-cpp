rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
./Mandelbrot 800 800 60