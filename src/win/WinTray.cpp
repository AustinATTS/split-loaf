#include "WinTray.h"
#include <shellapi.h>
#define IDI_APP_ICON 101

NOTIFYICONDATA nid;
HMENU hMenu = NULL;

void InitTrayIcon(HWND hwnd) {
    ZeroMemory(&nid, sizeof(nid));
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    nid.uCallbackMessage = WM_USER + 1;

    // Load a custom icon from resource (IDI_MYICON)
    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APP_ICON), IMAGE_ICON,GetSystemMetrics(SM_CYICON),GetSystemMetrics(SM_CXICON),LR_DEFAULTCOLOR);
    strcpy_s(nid.szTip, "Split Loaf - Idle");
    nid.hIcon = hIcon;
    Shell_NotifyIcon(NIM_ADD, &nid);

    // Create context menu
    hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING, 1, "Settings");
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, 2, "Exit");
}

void RemoveTrayIcon() {
    Shell_NotifyIcon(NIM_DELETE, &nid);
    if(hMenu) DestroyMenu(hMenu);
}

void ShowTrayMenu(HWND hwnd) {
    POINT pt;
    GetCursorPos(&pt);
    SetForegroundWindow(hwnd); // required for menu to disappear correctly
    TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
}
