#include "WinBackend.h"
#include "WinHooks.h"
#include <windows.h>

static HHOOK keyboardHook = NULL;
static HWND targetWindow = NULL;
static bool locked = false;
static bool targetHasFocus = false;

HHOOK& WinHooks_GetKeyboardHook() { return keyboardHook; }
HWND& WinHooks_GetTargetWindow() { return targetWindow; }
bool& WinHooks_GetLockedFlag() { return locked; }
bool& WinHooks_GetTargetFocusFlag() { return targetHasFocus; }

void WinBackend::init() {
    keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        LowLevelKeyboardProc,
        GetModuleHandle(NULL),
        0
    );
}

void WinBackend::shutdown() {
    UnhookWindowsHookEx(keyboardHook);
}

void WinBackend::setTargetWindow(WindowHandle w) {
    targetWindow = (HWND)w;
}

void WinBackend::lockInput() {
    locked = true;
}

void WinBackend::unlockInput() {
    locked = false;
    targetHasFocus = false;
}

void WinBackend::sendVirtualKey(uint32_t vk) {
    INPUT in[2] = {0};

    in[0].type = INPUT_KEYBOARD;
    in[0].ki.wVk = vk;

    in[1].type = INPUT_KEYBOARD;
    in[1].ki.wVk = vk;
    in[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, in, sizeof(INPUT));
}

bool WinBackend::processEvents() {
    MSG msg;
    return GetMessage(&msg, NULL, 0, 0) > 0;
}
