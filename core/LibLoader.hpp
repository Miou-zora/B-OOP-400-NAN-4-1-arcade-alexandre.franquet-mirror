/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** LibLoader
*/

#pragma once
#include <string>
#include <memory.h>
#include <dlfcn.h>
#include "ErrorManagement.hpp"

namespace Arcade {
    template <typename LibInterface>
        class LibLoader {
            /**
             * @class LibLoader
             *  @brief The class LibLoader is the class that loads the libraries
             *  @details It is using a template to be able to load any type of library
             *  @details The template must be a IDisplay or a IGame or a ISounds or a IEvent
            **/
            public:
                LibLoader(void) {};
                ~LibLoader() {};

                /**
                 * @brief Loads a library
                 * @param libPath The name of the library to load
                 * @return A shared pointer to the library
                 * @details The library must be in the ./lib folder
                 **/
                std::shared_ptr<LibInterface> loadGraphicalLib(const std::string &libPath)
                {
                    _handle = dlopen(libPath.c_str(), RTLD_LAZY);
                    LibInterface *(*builder)() = nullptr;
                    if (!_handle)
                        throw LoaderException(dlerror());
                    builder = reinterpret_cast<LibInterface *(*)()>(dlsym(_handle, "DisplayEntryPoint"));
                    if (!builder)
                        throw LoaderException(dlerror());
                    return std::shared_ptr<LibInterface>(builder());
                }

                std::shared_ptr<LibInterface> loadGameLib(const std::string &libPath)
                {
                    _handle = dlopen(libPath.c_str(), RTLD_LAZY);
                    LibInterface *(*builder)() = nullptr;
                    if (!_handle)
                        throw LoaderException(dlerror());
                    builder = reinterpret_cast<LibInterface *(*)()>(dlsym(_handle, "GameEntryPoint"));
                    if (!builder)
                        throw LoaderException(dlerror());
                    return std::shared_ptr<LibInterface>(builder());
                }

                void closeLib()
                {
                    if (dlclose(_handle) != 0)
                        throw LoaderException(dlerror());
                }

                bool isLibOpen() const
                {
                    return _handle != nullptr;
                }

                private:
                    void *_handle;
        };
};
