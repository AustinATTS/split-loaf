cmake_minimum_required(VERSION 4.0)
project(split_loaf LANGUAGES C CXX RC)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    enable_language(RC)

    add_executable(split-loaf
            src/app/main.cpp
            src/core/Platform.cpp
            src/win/WinBackend.cpp
            src/win/WinHooks.cpp
            src/win/WinTray.cpp
            src/win/WinApp.cpp
            src/win/WinSettings.cpp
            src/core/Backend.h
            src/res/resource.rc
    )

    target_include_directories(split-loaf PUBLIC src)
    target_link_libraries(split-loaf user32 gdi32 shell32)
else()
    add_executable(split-loaf
            src/app/main.cpp
            src/core/Platform.cpp
            src/linux/LinuxBackend.cpp
            src/linux/LinuxHooks.cpp
            src/core/Backend.h
    )
endif()