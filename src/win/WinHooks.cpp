#include "WinHooks.h"
#include "WinBackend.h"
#include <windows.h>
#include <stdio.h>

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

            WinBackend::sendVirtualKey (kbd->vkCode);
            return 1;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
