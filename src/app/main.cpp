#ifdef _WIN32 // Will only build the Windows version for Windows devices.
#include <windows.h>
extern int RunWindowsApp ( );

// Windows expects a WinMain as the application entry point so it doesn't attempt to run it through the terminal.
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    return RunWindowsApp(); // Call the main start function from WinApp.cpp.
}
#else // For other operating systems just return 0 as they haven't been implemented yet.
extern int linux_main ( );
int main ( ) {
    return linux_main();
}
#endif
