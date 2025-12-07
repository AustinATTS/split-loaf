#include "WinBackend.h"
#include "WinHooks.h"
#include <windows.h>
#include "WinTray.h"
#include "core/Platform.h"

// IDs for handling the button events.
#define TRAY_CALLBACK (WM_USER + 1)
#define CMD_SETTINGS 1001
#define CMD_EXIT 1002

static HHOOK keyboardHook = NULL;
static HWND targetWindow = NULL;
static bool locked = false;
static bool targetHasFocus = false;

HHOOK & WinHooks_GetKeyboardHook ( ) {
    return keyboardHook; // Gives the keyboard hook.
}
HWND & WinHooks_GetTargetWindow ( ) {
    return targetWindow; // Gives the target window.
}
bool & WinHooks_GetLockedFlag ( ) {
    return locked; // Gives the current state of locked.
}
bool & WinHooks_GetTargetFocusFlag ( ) {
    return targetHasFocus; // Gives the state of the target window.
}

void WinBackend::init ( ) { // Sets up the keyboard hook.
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc,GetModuleHandle(NULL),0);
}

void WinBackend::shutdown ( ) { // Removes the hook when closed.
    UnhookWindowsHookEx(keyboardHook);
}

void WinBackend::setTargetWindow (WindowHandle w) {
    targetWindow = (HWND) w; // Sets the target window.
}

void WinBackend::lockInput ( ) {
    locked = true; // Sets the locked value.
}

void WinBackend::unlockInput ( ) {
    locked = false; // Unlock the keyboard.
    targetHasFocus = false;
}

void WinBackend::sendVirtualKey (uint32_t vk) {
    // Send a key down signal to the target window.
    // Key up isn't important so can be left to be handled by Windows to allow modifier keys to be used.
    INPUT in = {0};

    in.type = INPUT_KEYBOARD;
    in.ki.wVk = vk;

    SendInput(1, & in, sizeof(INPUT));
}

bool WinBackend::processEvents ( ) { // Handle processes.
    return true;
}
