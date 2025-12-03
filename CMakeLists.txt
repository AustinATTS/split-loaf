cmake_minimum_required(VERSION 4.0)
project(split_loaf LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(split-loaf
        src/app/main.cpp
        src/core/Platform.cpp
        src/win/WinBackend.cpp
        src/win/WinHooks.cpp
        src/win/WinTray.cpp
        src/core/Backend.h
        src/res/resource.rc
)

target_include_directories(split-loaf PUBLIC src)
target_link_libraries(split-loaf user32)
