cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    project(split_loaf LANGUAGES C CXX RC)
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

    target_link_options(split-loaf PRIVATE -static -static-libgcc -static-libstdc++)
    target_include_directories(split-loaf PUBLIC src)
    target_link_libraries(split-loaf user32 gdi32 shell32)
    set_target_properties(split-loaf PROPERTIES WIN32_EXECUTABLE TRUE)

else()
    project(split_loaf LANGUAGES C CXX)

    add_executable(split-loaf
            src/app/main.cpp
            src/core/Platform.cpp
            src/linux/LinuxBackend.cpp
            src/linux/LinuxHooks.cpp
            src/core/Backend.h
            src/linux/linux_test.c
    )
endif()