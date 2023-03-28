# Base Architecture for the Arcade Project

## Interfaces

Since the main goal of the project is to have multiple different libs used through the same interface, there is 4 of them :
- IDisplay
- IObject
- ICMakeme
- ISound

## Build
To build the project:
```
sh cmake . && make
```
Then you'll have a makefile build. But not an Epitech one. Use ```make clean``` instead of the ```make fclean```

You should watch this video to understand cmake : [CMake](https://www.youtube.com/watch?v=mKZ-i-UfGgQ&ab_channel=kandodev)
