<h1 align="center">
	<img src="https://github.com/AustinATTS/split_loaf/blob/master/assets/Logo/Split%20Loaf%202160x2160.png" width="" height="250" alt="Logo"/></br>
	Split Loaf - Keyboard Rerouter
</h1>

**Status:** Version 1.0.0 – Fully Released 🎉

[![Microsoft Store Page](https://get.microsoft.com/images/en-us%20light.svg)](https://apps.microsoft.com/detail/9nfhj4ptjxkv?hl=en-GB&gl=GB)

[![Windows Build Status](https://github.com/AustinATTS/split_loaf/actions/workflows/build.yml/badge.svg)](https://github.com/AustinATTS/split_loaf/actions/workflows/build.yml)  [![Linux Build Status](https://github.com/AustinATTS/split_loaf/actions/workflows/build_linux.yml/badge.svg)](https://github.com/AustinATTS/split_loaf/actions/workflows/build_linux.yml)

Overview
--------

Split Loaf is a Windows utility designed to reroute keyboard input to a specific target window. Once a target window is chosen, the keyboard can be **“locked”** to that window, so all typed keys are sent directly to it regardless of which window is currently focused. This is perfect for scenarios where you want input to always go to a particular application without manually switching focus—for example, browsing the web while typing into a text editor without moving your mouse.

Version 1.0.0 marks the first full Windows release, with a stable executable, system tray integration, and persistent keybind and startup settings via the Windows Registry.

Features
--------

* **Select Target Window**: Press **F8** to pick a window under your cursor as the target.
* **Lock Keyboard**: Press **F6** to lock all keyboard input to the selected window.
* **Unlock Keyboard**: Press **F7** to release the lock and restore normal keyboard behaviour.
* **Direct Input Injection**: Keys are sent directly to the target window automatically.
* **Custom Keybinds**: Reassign the default function keys to any keys you like via the settings.
* **System Tray Integration**: Live tooltips show your current target and lock state.
* **Persistent Settings**: Run on startup and keybind configurations are stored in the Windows Registry, surviving restarts and updates.

Current Development Status
--------------------------

Split Loaf 1.0.0 is now a stable release for Windows. Some limitations still exist:

* Non-standard input (like Unicode or multi-character sequences) may not be fully supported.
* Currently Windows-only; cross-platform support is still in development.
* Some applications may behave unexpectedly depending on how they handle low-level keyboard messages.

How It Works
------------

1. Press **F8** to select a target window.
2. Press **F6** to lock the keyboard to that window.
3. All typed keys are sent directly to the target window.
4. Press **F7** to unlock the keyboard and return to normal input behaviour.

Internally, Split Loaf uses a **low-level keyboard hook** and sends messages directly to the target window. Modifier keys are preserved while locked.

Linux Versions
--------------

Split Loaf currently relies on Windows APIs, so Linux support requires a different method for keyboard input and window detection. Early testing on Wayland (Hyprland with Arch) shows partial functionality, but challenges exist with active window detection and input security protocols. Further exploration is ongoing.

Future Improvements
-------------------

* Full Unicode and symbol input handling.
* Optional visual indicator for lock state.
* Cross-platform support for Linux and other OSes.
* Windows notifications for lock/unlock events.

Installation
------------

GitHub
1. Download the latest [Windows executable](https://github.com/AustinATTS/split_loaf/releases/latest).  
2. Move it to your preferred location.  
3. Run it.  
4. (Optional) Enable **Run on Startup** to have Split Loaf launch automatically with Windows.

Microsoft Store
1. Download from the [Microsoft Store](https://apps.microsoft.com/detail/9nfhj4ptjxkv?referrer=appbadge&mode=direct).
2. Run it.
3. (Optional) Enable **Run on Startup** to have Split Loaf launch automatically with Windows.

Contact
-------

For questions, bug reports, or feature suggestions:

**Austin Welsh-Graham**  
Email: [admin@toastysoftware.co.uk](mailto:admin@toastysoftware.co.uk)
