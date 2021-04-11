# triangle

## Building the project
### Linux
CMake
```
mkdir build
cd build
cmake ..
make
```

or with command line
```
g++ main.cpp -lGL -lX11 -o triangle
```

### macOS
You can also compile this on mac, but you need XQuartz.
Compile with CMake or command line
```
$ g++ main.cpp -I/opt/X11/include  -L/opt/X11/lib -lGL -lX11 -o triangle
```
