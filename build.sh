mkdir build
cd build

CC=/usr/bin/clang-14 CXX=/usr/bin/clang++-14 cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G Ninja
ninja

