del CMakeCache.txt /s
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release,Debug -G "Visual Studio 15 2017 Win64" -DBUILD_EXAMPLES=ON
