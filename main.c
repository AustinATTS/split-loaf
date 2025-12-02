#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <stdio.h>

HHOOK keyboardHook;
HWND targetWindow = NULL;
int locked = 0;

void SendVirtualKeyToTarget(DWORD vkCode) {
    INPUT in[2] = {0};

    // Key down
    in[0].type = INPUT_KEYBOARD;
    in[0].ki.wVk = vkCode;
    in[0].ki.dwFlags = 0;

    // Key up
    in[1].type = INPUT_KEYBOARD;
    in[1].ki.wVk = vkCode;
    in[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, in, sizeof(INPUT));
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *)lParam;

        // Ignore synthetic keystrokes we injected ourselves
        if (kbd->flags & LLKHF_INJECTED) {
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        }

        if (wParam == WM_KEYDOWN) {
            if (kbd->vkCode == VK_F6) {
                locked = (targetWindow != NULL);
                printf("Locked: %d\n", locked);
                return 1;
            }

            if (kbd->vkCode == VK_F7) {
                locked = 0;
                printf("Unlocked\n");
                return 1;
            }

            if (kbd->vkCode == VK_F8) {
                POINT p;
                GetCursorPos(&p);
                targetWindow = WindowFromPoint(p);
                printf("Target window: 0x%p\n", targetWindow);
                return 1;
            }
        }

        // Reroute keystrokes
        if (locked && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
            if (targetWindow) {
                HWND prev = GetForegroundWindow();
                SetForegroundWindow(targetWindow);
                Sleep(1);

                SendVirtualKeyToTarget(kbd->vkCode);

                if (prev) {
                    SetForegroundWindow(prev);
                }

                return 1; // swallow original
            }
        }
        /*
        if (locked && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
            if (targetWindow) {

                // Send key directly to the target window WITHOUT switching focus
                PostMessage(targetWindow, WM_KEYDOWN, kbd->vkCode, 0);

                // swallow original key
                return 1;
            }
        }

        if (locked && (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)) {
            if (targetWindow) {
                PostMessage(targetWindow, WM_KEYUP, kbd->vkCode, 0);
                return 1;
            }
        }
        */

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