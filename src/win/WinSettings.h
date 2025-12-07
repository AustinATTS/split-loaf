#pragma once
#include <windows.h>
#include <string>

struct Keybind {
    UINT key;
    bool ctrl;
    bool shift;
    bool alt;
};

const Keybind & WinSettings_GetTargetBind ( );
const Keybind & WinSettings_GetLockBind ( );
const Keybind & WinSettings_GetUnlockBind ( );

void OpenSettingsWindow (HINSTANCE hInstance, HWND parent);
void WinSettings_Init ( );

