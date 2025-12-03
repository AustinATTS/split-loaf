#include "WinBackend.h"
#include "WinHooks.h"
#include <windows.h>
#include "WinTray.h"
#include "core/Platform.h"

#define TRAY_CALLBACK (WM_USER + 1)

#define CMD_SETTINGS 1001
#define CMD_EXIT     1002


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
    INPUT in = {0};

    in.type = INPUT_KEYBOARD;
    in.ki.wVk = vk;


    SendInput(1, &in, sizeof(INPUT));
}

bool WinBackend::processEvents() {
    MSG msg;
    return GetMessage(&msg, NULL, 0, 0) > 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case TRAY_CALLBACK:
            if (lParam == WM_RBUTTONUP)
                ShowTrayMenu(hwnd);
            break;

        case WM_COMMAND: // menu selection
            switch(LOWORD(wParam)) {
            case CMD_SETTINGS:
                    break;
            case CMD_EXIT:
                    PostQuitMessage(0);
                    break;
            }
            break;

        case WM_DESTROY:
            RemoveTrayIcon();
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int RunWindowsApp(HINSTANCE hInstance) {
    const char CLASS_NAME[] = "SplitLoafTray";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Split Loaf",
        0, 0, 0, 0, 0,
        NULL, NULL, hInstance, NULL
    );

    InitTrayIcon(hwnd);

    // --- Core Platform initialization ---
    Platform::init();

    MSG msg = {};
    while (true) {
        // Process Windows messages
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                goto quit;
        }

        // Process your platform-specific events
        Platform::processEvents();
    }

    quit:
        Platform::shutdown();
    return 0;
}

