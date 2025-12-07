#include "WinTray.h"
#include <shellapi.h>
#include <string>
#include <algorithm>

// Define a value for the app icon.
#define IDI_APP_ICON 101

NOTIFYICONDATA nid;
HMENU hMenu = NULL;

void InitTrayIcon (HWND hwnd) { // Create the system tray icon.
    ZeroMemory(& nid, sizeof(nid));
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    nid.uCallbackMessage = WM_USER + 1;

    // Use load image as the icon one doesn't seem to work.
    HICON hIcon = (HICON) LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_APP_ICON),IMAGE_ICON,GetSystemMetrics(SM_CXICON),GetSystemMetrics(SM_CYICON),LR_DEFAULTCOLOR);

    nid.hIcon = hIcon;
    strncpy_s(nid.szTip, "Split Loaf - Idle", sizeof(nid.szTip));

    Shell_NotifyIcon(NIM_ADD, & nid);

    hMenu = CreatePopupMenu(); // Create a popup for the right click menu.
    AppendMenu(hMenu, MF_STRING, 1001, "Settings");
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, 1002, "Exit");
}

void RemoveTrayIcon ( ) { // Delete the tray icon.
    Shell_NotifyIcon(NIM_DELETE, & nid);
    if (hMenu) { // If it exists then destroy it.
        DestroyMenu(hMenu);
        hMenu = NULL;
    }
}

void ShowTrayMenu (HWND hwnd) { // Show the tray icon.
    POINT pt;
    GetCursorPos(& pt);
    SetForegroundWindow(hwnd);
    TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
}

void UpdateTrayTooltip (const std::string & status) { // Update the tooltip to represent the current state of the program.
    strncpy_s(nid.szTip, status.c_str(), sizeof(nid.szTip) - 1);
    nid.uFlags = NIF_TIP;
    Shell_NotifyIcon(NIM_MODIFY, & nid);
}
