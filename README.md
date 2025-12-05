Split Loaf Keyboard Rerouter [![Split Loaf](https://github.com/AustinATTS/split_loaf/blob/master/assets/splitloaf.png)](https://github.com/AustinATTS/split_loaf/blob/master/assets/splitloaf.png)
============================

**Status:** Somehow working?

[![Windows Build Status](https://github.com/AustinATTS/split_loaf/actions/workflows/build.yml/badge.svg)](https://github.com/AustinATTS/split_loaf/actions/workflows/build.yml)  [![Linux Build Status](https://github.com/AustinATTS/split_loaf/actions/workflows/build_linux.yml/badge.svg)](https://github.com/AustinATTS/split_loaf/actions/workflows/build_linux.yml)

Overview
--------

Split Loaf is a Windows utility designed to reroute keyboard input to a specific target window. Once a target window is chosen, the keyboard can be “locked” to that window, so that all typed keys are sent directly to it regardless of which window is currently focused. This is useful for scenarios where you want input to always go to a particular application without manually switching focus.
For example if you'd like to keep browsing through Google while still typing in a text editor without the need to move your mouse around.

Features
--------

*   **Select Target Window**: Press **F8** to pick a window under your cursor as the target.

*   **Lock Keyboard**: Press **F6** to lock all keyboard input to the selected window.

*   **Unlock Keyboard**: Press **F7** to release the lock and restore normal keyboard behaviour.

*   **Direct Input Injection**: Keys are sent directly to the target window automatically.


Current Development Status
--------------------------

Split Loaf is still under active development. The current version works but has a few known limitations:

*   Non-standard input (like Unicode or multi-character inputs) may not be fully supported.

*   Currently limited to Windows; cross-platform support is not implemented.

*   Some applications may behave unexpectedly due to how they handle low-level keyboard messages.


How It Works
------------

1.  Press **F8** to select a target window.

2.  Press **F6** to lock the keyboard to that window.

3.  All typed keys are sent directly to the target window.

4.  Press **F7** to unlock the keyboard and return to normal input behaviour.


Internally, the program uses a **low-level keyboard hook** and sends messages directly to the target window. It ignores key up so modifier keys can still be used.

Future Improvements
-------------------

*   Unicode and symbol input handling.

*   Optional visual indicator for lock state.

Linux Versions
-------------

Currently, the version of Split Loaf relies on Windows API for handling the keyboard redirection and so a new method will be needed for accessing keyboard input on linux or other devices to be able to handle them as well as for finding the window ID of what is being used. A possible issue could be in environments like hyprland which bases the active window solely on where the mouse is, instead of having a separate active window and so might be hard to do, but I'll give it a go because why not.

Different linux distros might handle this differently as well, currently using wayland for arch so that will be what I develop for first.

The test file given for linux has shown to somewhat work when used on hyprland (wayland) with arch however doesn't with crosinti penguin so they might handle inputs in different ways. It does this based on a given command to output space where if you are quick enough to move to a different window, it will send the space to that window and so it will need to be modified such that it can also switch to the target window automatically as well as give the output based on what the user tpes in.

Wayland has some weird security protocols in the way it handles windows so it may be difficult to work, a scripting languages that can execute terminal xommands might be better suited so I'll need to look into this and see if it could be a suitable suggestion.

Contact
-------

For questions, bug reports, or feature suggestions:

**Austin Welsh-Graham**

Email: [admin@toastysoftware.co.uk](mailto:admin@toastysoftware.co.uk)
