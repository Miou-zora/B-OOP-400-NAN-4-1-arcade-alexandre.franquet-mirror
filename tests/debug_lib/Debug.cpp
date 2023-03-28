#include "Debug.hpp"

extern "C"
{
    Arcade::IDisplay *entryPoint()
    {
        return new DebugModule();
    }
}
