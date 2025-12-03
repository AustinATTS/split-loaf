Split Loaf Keyboard Rerouter
============================

**Status:** Somehow working?

[![Windows Build Status](https://github.com/AustinATTS/split_loaf/actions/workflows/build.yml/badge.svg)](https://github.com/AustinATTS/split_loaf/actions/workflows/build.yml)

Overview
--------

Split Loaf is a Windows utility designed to reroute keyboard input to a specific target window. Once a target window is chosen, the keyboard can be “locked” to that window, so that all typed keys are sent directly to it regardless of which window is currently focused. This is useful for scenarios where you want input to always go to a particular application without manually switching focus.
For example if you'd like to keep browsing through Google while still typing in a text editor without the need to switch windows.

Features
--------

*   **Select Target Window**: Press **F8** to pick a window under your cursor as the target.

*   **Lock Keyboard**: Press **F6** to lock all keyboard input to the selected window.

*   **Unlock Keyboard**: Press **F7** to release the lock and restore normal keyboard behaviour.

*   **Direct Input Injection**: Keys are sent directly to the target window without switching focus, preventing focus-thrashing.


Current Development Status
--------------------------

Split Loaf is still under active development. The current version works but has a few known limitations:

*   It is weirdly slow and gives double inputs or can miss inputs.

*   Modifier keys (Shift, Ctrl, Alt) may not always combine correctly with letter or symbol keys.

*   Non-standard input (like Unicode or multi-character inputs) may not be fully supported.

*   Currently limited to Windows; cross-platform support is not implemented.

*   Some applications may behave unexpectedly due to how they handle low-level keyboard messages.


How It Works
------------

1.  Press **F8** to select a target window.

2.  Press **F6** to lock the keyboard to that window.

3.  All typed keys are sent directly to the target window.

4.  Press **F7** to unlock the keyboard and return to normal input behaviour.


Internally, the program uses a **low-level keyboard hook** and posts messages directly to the target window. It ignores injected keystrokes to prevent double typing and aims to minimize focus conflicts.

Future Improvements
-------------------

*   Full modifier key support (Shift, Ctrl, Alt).

*   Unicode and symbol input handling.

*   Optional visual indicator for lock state.

Linux Versions
-------------

Currently, the version of Split Loaf relies on Windows API for handling the keyboard redirection and so a new method will be needed for accessing keyboard input on linux or other devices to be able to handle them as well as for finding the window ID of what is being used. A possible issue could be in environments like hyprland which bases the active window solely on where the mouse is, instead of having a separate active window and so might be hard to do, but I'll give it a go because why not.

Different linux distros might handle this differently as well, currently using wayland for arch so that will be what i develop for first.

Contact
-------

For questions, bug reports, or feature suggestions:

**Austin Welsh-Graham**

Email: [admin@toastysoftware.co.uk](mailto:admin@toastysoftware.co.uk)
