# Base Architecture for the Arcade Project

## Interfaces

Since the main goal of the project is to have multiple different libs used through the same interface, there is 2 of them :
- ILib
- IGame

## Build
To build the project:
```sh
∼/B-OOP-400> mkdir ./build/ && cd ./build/
∼/B-OOP-400/build> cmake .. -G “Unix Makefiles” -DCMAKE_BUILD_TYPE=Release
[...]
∼/B-OOP-400/build> cmake --build .
[...]
∼/B-OOP-400/build> cd ..
∼/B-OOP-400> ls ./arcade ./lib/
./arcade

./lib/:

arcade_ncurses.so
arcade_sdl2.so
arcade_sfml.so
arcade_snake.so
arcade_nibbler.so
```
Then you'll have a makefile build. But not an Epitech one. Use `make clean` instead of the `make fclean`.

You should watch this video to understand cmake : [CMake](https://www.youtube.com/watch?v=mKZ-i-UfGgQ&ab_channel=kandodev)

By `Dlore` made up of:
 - [Alexandre Franquet | Miouzora](https://github.com/Miou-zora)
 - [Quentin Brejoin | Queng](https://github.com/queng123)
 - [Guylain Thomas | Jibea](https://github.com/Jibea)

In collaboration with `C11H17NO3` made up of:
 - [Timothee Lesellier | Big T](https://github.com/BigT-Dev)
 - [Lylian Hay | VyOk](https://github.com/lhay9)
 - [Mathis Evain | Kibatsu](https://github.com/Kibatsu03)
