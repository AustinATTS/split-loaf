#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <stdio.h>

HHOOK keyboardHook;
HWND targetWindow = NULL;
int locked = 0;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *)lParam;

        // Hotkeys
        if (wParam == WM_KEYDOWN) {
            if (kbd->vkCode == VK_F6) {  // Lock
                locked = (targetWindow != NULL);
                printf("Locked: %d\n", locked);
                return 1; // suppress key
            }
            if (kbd->vkCode == VK_F7) {  // Unlock
                locked = 0;
                printf("Unlocked\n");
                return 1;
            }
            if (kbd->vkCode == VK_F8) {  // Set target window
                POINT p;
                GetCursorPos(&p);
                targetWindow = WindowFromPoint(p);
                printf("Target window: 0x%p\n", targetWindow);
                return 1;
            }
        }

        // Reroute typing
        if (locked && wParam == WM_KEYDOWN && targetWindow != NULL) {
            BYTE keyState[256];
            GetKeyboardState(keyState);

            WCHAR buff[2];
            int res = ToUnicode(kbd->vkCode, kbd->scanCode, keyState, buff, 2, 0);

            if (res > 0) {
                // Send each character
                for (int i = 0; i < res; i++) {
                    PostMessageW(targetWindow, WM_CHAR, buff[i], 0);
                }
            }

            return 1; // swallow key globally
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    printf("Split Loaf daemon running...\n");
    printf("F8 = Set target window\n");
    printf("F6 = Lock keyboard\n");
    printf("F7 = Unlock keyboard\n");

    keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        LowLevelKeyboardProc,
        GetModuleHandle(NULL),
        0
    );

    if (!keyboardHook) {
        printf("Failed to install hook.\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {}

    UnhookWindowsHookEx(keyboardHook);
    return 0;
}