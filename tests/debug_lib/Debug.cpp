#include "Debug.hpp"

extern "C"
{
    Arcade::ILib *DisplayEntryPoint()
    {
        return new DebugModule();
    }
}
