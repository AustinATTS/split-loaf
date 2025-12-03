#include "core/Platform.h"
#include "win/WinApp.h"   // runs the Windows GUI loop

int main() {
#ifdef _WIN32
    return RunWindowsApp();
#else
    // other OS logic later
    Platform::init();
    Platform::processEvents();
    Platform::shutdown();
    return 0;
#endif
}
