if [ ! -d build ]; then
    mkdir build
    cd build
    cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G Ninja
else
    cd build
fi

ninja
cd ..
