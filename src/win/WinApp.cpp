#include <windows.h>
#include "WinApp.h"
#include "WinTray.h"
#include "core/Platform.h"
#include "WinSettings.h"

static const char * WINDOW_CLASS = "SplitLoafTray";
static HINSTANCE g_hInstance = NULL;

LRESULT CALLBACK WindowProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case TRAY_CALLBACK:
            if (lParam == WM_RBUTTONUP) {
                ShowTrayMenu(hwnd);
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
            case CMD_SETTINGS:
                    OpenSettingsWindow(g_hInstance, hwnd);
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

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int RunWindowsApp ( ) {
    HANDLE hMutex = CreateMutexA(NULL, TRUE, "Global//SplitLoaf");
    if (! hMutex) {
        MessageBoxA(NULL, "Failed to create mutex.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        MessageBoxA(NULL, "Split Loaf is already running.", "Info", MB_OK | MB_ICONINFORMATION);
        CloseHandle(hMutex);
        return 0;
    }

    g_hInstance = GetModuleHandle(NULL);

    WinSettings_Init();

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = g_hInstance;
    wc.lpszClassName = WINDOW_CLASS;
    RegisterClass(& wc);

    HWND hwnd = CreateWindowEx(0, WINDOW_CLASS, "Split Loaf", 0, 0, 0, 0, 0, NULL, NULL, g_hInstance, NULL);

    InitTrayIcon(hwnd);
    Platform::init();

    MSG msg{};
    while (true) {
        DWORD result = MsgWaitForMultipleObjects(0, NULL, FALSE, 1, QS_ALLINPUT);

        if (result == WAIT_OBJECT_0) {
            while (PeekMessage(& msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(& msg);
                DispatchMessage(& msg);

                if (msg.message == WM_QUIT) {
                    Platform::shutdown();
                    ReleaseMutex(hMutex);
                    CloseHandle(hMutex);
                    return 0;
                }
            }
        }
        Platform::processEvents();
    }
}
