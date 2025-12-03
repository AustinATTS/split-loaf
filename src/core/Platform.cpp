#include "Platform.h"
#include "../win/WinBackend.h"

namespace Platform {

    void init() {
        WinBackend::init();
    }

    void shutdown() {
        WinBackend::shutdown();
    }

    void setTargetWindow(WindowHandle w) {
        WinBackend::setTargetWindow(w);
    }

    void lockInput() {
        WinBackend::lockInput();
    }

    void unlockInput() {
        WinBackend::unlockInput();
    }

    bool processEvents() {
        return WinBackend::processEvents();
    }

}
