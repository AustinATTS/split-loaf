// src/core/Backend.h
#pragma once
#include <stdint.h>

using WindowHandle = void*;  // platform-specific opaque type

class Backend {
public:
    virtual ~Backend() = default;

    virtual void init() = 0;
    virtual void shutdown() = 0;

    virtual void setTargetWindow(WindowHandle w) = 0;
    virtual void lockInput() = 0;
    virtual void unlockInput() = 0;

    virtual void sendVirtualKey(uint32_t key) = 0;

    virtual bool processEvents() = 0;
};
