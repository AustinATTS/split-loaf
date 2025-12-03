#include "WinHooks.h"
#include "WinBackend.h"
#include <windows.h>
#include <stdio.h>

void SendVirtualKeyToTarget(DWORD vkCode) {
    INPUT in[2] = {0};

    in[0].type = INPUT_KEYBOARD;
    in[0].ki.wVk = vkCode;

    in[1].type = INPUT_KEYBOARD;
    in[1].ki.wVk = vkCode;
    in[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, in, sizeof(INPUT));
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode != HC_ACTION)
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    auto& targetWindow = WinHooks_GetTargetWindow();
    auto& locked = WinHooks_GetLockedFlag();
    auto& targetHasFocus = WinHooks_GetTargetFocusFlag();

    KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT*)lParam;

    if (kbd->flags & LLKHF_INJECTED)
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    if (wParam == WM_KEYDOWN) {
        if (kbd->vkCode == VK_F8) {
            POINT p;
            GetCursorPos(&p);
            targetWindow = WindowFromPoint(p);
            printf("Target window: 0x%p\n", targetWindow);
            return 1;
        }

        if (kbd->vkCode == VK_F6) {
            locked = (targetWindow != NULL);
            if (locked) {
                SetForegroundWindow(targetWindow);
                Sleep(1);
                targetHasFocus = 1;
            }
            printf("Locked: %d\n", locked);
            return 1;
        }

        if (kbd->vkCode == VK_F7) {
            locked = false;
            targetHasFocus = false;
            printf("Unlocked\n");
            return 1;
        }
    }

    if (locked && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        if (targetWindow) {
            HWND fg = GetForegroundWindow();

            if (fg != targetWindow) {
                SetForegroundWindow(targetWindow);
                Sleep(1);
                targetHasFocus = 1;
            }

            SendVirtualKeyToTarget(kbd->vkCode);
            return 1;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
