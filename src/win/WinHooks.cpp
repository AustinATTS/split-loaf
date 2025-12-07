#include "WinHooks.h"
#include "WinBackend.h"
#include <windows.h>
#include "WinTray.h"
#include <stdio.h>
#include <string>
#include <algorithm>
#include "WinSettings.h"

const Keybind targetBind = WinSettings_GetTargetBind();
const Keybind lockBind = WinSettings_GetLockBind();
const Keybind unlockBind = WinSettings_GetUnlockBind();

std::string ToLower (const std::string & s) { // Set the string to lowercase.
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}

std::string ToUpper (const std::string & s) { // Set the string to uppercase.
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(), ::toupper);
    return out;
}

std::string GetWindowTitle (HWND hwnd) { // Get the name of the target window.
    char buffer[256];
    GetWindowTextA(hwnd, buffer, sizeof(buffer));
    return std::string(buffer);
}

void Tray_SetIdle ( ) { // Set the tooltip for the System Tray to indicate state of the program as idle.
    UpdateTrayTooltip("Split Loaf - Idle");
}

void Tray_SetTargeted (const std::string & windowName) {
    UpdateTrayTooltip("Split Loaf - " + ToLower(windowName)); // When a window is targeted it shows the app name in lowercase.
}

void Tray_SetLocked (const std::string & windowName) {
    UpdateTrayTooltip("Split Loaf - " + ToUpper(windowName)); // When the keyboard is locked, the name of the window is shown in capitals.
}

bool IsKeybindPressed(const Keybind & bind, KBDLLHOOKSTRUCT * kbd) {
    bool ctrlDown  = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
    bool shiftDown = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    bool altDown   = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0; // ALT

    return (kbd -> vkCode == bind.key) && (ctrlDown == bind.ctrl) && (shiftDown == bind.shift) && (altDown == bind.alt);
}


LRESULT CALLBACK LowLevelKeyboardProc (int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode != HC_ACTION) {
        // If no action go to next.
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    // Get the current values of the program state.
    auto & targetWindow = WinHooks_GetTargetWindow();
    auto & locked = WinHooks_GetLockedFlag();
    auto & targetHasFocus = WinHooks_GetTargetFocusFlag();

    KBDLLHOOKSTRUCT * kbd = (KBDLLHOOKSTRUCT *) lParam;

    if (kbd -> flags & LLKHF_INJECTED) {
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    if (wParam == WM_KEYDOWN) { // For key press downs.
        if (IsKeybindPressed(WinSettings_GetTargetBind(), kbd)) {
            // If F8 is pressed set the target window to the current one.
            POINT p;
            GetCursorPos(& p);
            targetWindow = WindowFromPoint(p);
            if (targetWindow) {
                // If there is a suitable target window, update the tooltip and title.
                std::string title = GetWindowTitle(targetWindow);
                Tray_SetTargeted(title);
            } else {
                // If not a suitable target, set it to idle.
                Tray_SetIdle();
            }
            return 1;
        }

        if (IsKeybindPressed(WinSettings_GetLockBind(), kbd)) {
            // If F6 is pressed, lock the keyboard to the target window.
            locked = (targetWindow != NULL);
            if (locked) {
                // If valid, update tooltip and name.
                std::string title = GetWindowTitle(targetWindow);
                Tray_SetLocked(title);

                // Set the target window to be the main active window.
                SetForegroundWindow(targetWindow);
                Sleep(1);
                targetHasFocus = 1;
            }
            return 1;
        }

        if (IsKeybindPressed(WinSettings_GetUnlockBind(), kbd)) {
            // If F7 is pressed unlock the keyboard.
            locked = false;
            targetHasFocus = false;
            if (targetWindow) {
                // If valid update the name and tooltip.
                std::string title = GetWindowTitle(targetWindow);
                Tray_SetTargeted(title);
            } else {
                // If no valid window, set idle.
                Tray_SetIdle();
            }
            return 1;
        }
    }

    if (locked && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        // For key presses down while locked.
        if (targetWindow) { // If there is a target window.
            HWND fg = GetForegroundWindow();

            if (fg != targetWindow) { // If the target window is not the active one.
                SetForegroundWindow(targetWindow); // Make it active.
                Sleep(1); // Sleep so it can be processed.
                targetHasFocus = 1; // Say its been made active.
            }

            WinBackend::sendVirtualKey(kbd -> vkCode); // Redirect the keyboard presses.
            return 1;
        }
    }

    return CallNextHookEx (NULL, nCode, wParam, lParam); // Move to the next.
}

