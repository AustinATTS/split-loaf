#pragma once
#include <stdint.h>

using WindowHandle = void*;

namespace Platform {
    void init();
    void shutdown();

    void setTargetWindow(WindowHandle w);
    void lockInput();
    void unlockInput();

    bool processEvents();
}
