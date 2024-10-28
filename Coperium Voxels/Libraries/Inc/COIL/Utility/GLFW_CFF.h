#pragma once
#ifndef COIL_GLFW_CALLBACK_FUNCTION_FORMATS_H
#define COIL_GLFW_CALLBACK_FUNCTION_FORMATS_H

struct GLFWwindow;

namespace Coil {
    /* ============================================================================
     * ---------------------------- GLFW_errorfun
     * Error callback function.
     * Called when an error occurs in GLFW, providing the error code and description.
     *
     * ------ Parameters ------
     * error_code    The error code that identifies the error.
     * description   A human-readable description of the error.
     * ============================================================================
     */
    typedef void (*GLFW_Errorfun)(int error_code, const char* description);

    /* ============================================================================
     * ---------------------------- GLFW_windowposfun
     * Window position callback function.
     * Called when the window is moved. Provides the new X and Y positions of the window.
     *
     * ------ Parameters ------
     * window        The window that was moved.
     * xpos          The new X coordinate of the window.
     * ypos          The new Y coordinate of the window.
     * ============================================================================
     */
    typedef void (*GLFW_Windowposfun)(GLFWwindow* window, int xpos, int ypos);

    /* ============================================================================
     * ---------------------------- GLFW_windowsizefun
     * Window size callback function.
     * Called when the window is resized. Provides the new width and height of the window.
     *
     * ------ Parameters ------
     * window        The window that was resized.
     * width         The new width of the window in screen coordinates.
     * height        The new height of the window in screen coordinates.
     * ============================================================================
     */
    typedef void (*GLFW_Windowsizefun)(GLFWwindow* window, int width, int height);

    /* ============================================================================
     * ---------------------------- GLFW_Windowclosefun
     * Window close callback function.
     * Called when the window close event is triggered (e.g., by clicking the close button).
     *
     * ------ Parameters ------
     * window        The window that received the close event.
     * ============================================================================
     */
    typedef void (*GLFW_Windowclosefun)(GLFWwindow* window);

    /* ============================================================================
     * ---------------------------- GLFW_Windowrefreshfun
     * Window refresh callback function.
     * Called when the window needs to be redrawn, usually when the OS requests it.
     *
     * ------ Parameters ------
     * window        The window that needs to be redrawn.
     * ============================================================================
     */
    typedef void (*GLFW_Windowrefreshfun)(GLFWwindow* window);

    /* ============================================================================
     * ---------------------------- GLFW_Windowfocusfun
     * Window focus callback function.
     * Called when the window gains or loses input focus.
     *
     * ------ Parameters ------
     * window        The window that gained or lost focus.
     * focused       A boolean (1 for focused, 0 for unfocused).
     * ============================================================================
     */
    typedef void (*GLFW_Windowfocusfun)(GLFWwindow* window, int focused);

    /* ============================================================================
     * ---------------------------- GLFW_Windowiconifyfun
     * Window iconify callback function.
     * Called when the window is iconified (minimized) or restored.
     *
     * ------ Parameters ------
     * window        The window that was iconified or restored.
     * iconified     A boolean (1 for iconified, 0 for restored).
     * ============================================================================
     */
    typedef void (*GLFW_Windowiconifyfun)(GLFWwindow* window, int iconified);

    /* ============================================================================
     * ---------------------------- GLFW_Windowmaximisefun
     * Window maximised callback function.
     * Called when the window is maximised or restored.
     *
     * ------ Parameters ------
     * window        The window that was maximised or restored.
     * maximised     A boolean (1 for maximised, 0 for restored).
     * ============================================================================
     */
    typedef void (*GLFW_Windowmaximisefun)(GLFWwindow* window, int maximised);

    /* ============================================================================
     * ---------------------------- GLFW_Framebuffersizefun
     * Framebuffer size callback function.
     * Called when the framebuffer is resized, often due to a change in window size or scaling.
     *
     * ------ Parameters ------
     * window        The window whose framebuffer was resized.
     * width         The new width of the framebuffer in pixels.
     * height        The new height of the framebuffer in pixels.
     * ============================================================================
     */
    typedef void (*GLFW_Framebuffersizefun)(GLFWwindow* window, int width, int height);

    /* ============================================================================
     * ---------------------------- GLFW_Windowcontentscalefun
     * Window content scale callback function.
     * Called when the content scale of the window (DPI scaling) changes.
     *
     * ------ Parameters ------
     * window        The window whose content scale changed.
     * xscale        The new scale factor on the x-axis.
     * yscale        The new scale factor on the y-axis.
     * ============================================================================
     */
    typedef void (*GLFW_Windowcontentscalefun)(GLFWwindow* window, float xscale, float yscale);

    /* ============================================================================
     * ---------------------------- GLFW_Mousebuttonfun
     * Mouse button callback function.
     * Called when a mouse button is pressed or released.
     *
     * ------ Parameters ------
     * window        The window that received the event.
     * button        The mouse button that was pressed or released.
     * action        The button action (e.g., GLFW_PRESS or GLFW_RELEASE).
     * mods          Modifier keys (e.g., Shift, Control).
     * ============================================================================
     */
    typedef void (*GLFW_Mousebuttonfun)(GLFWwindow* window, int button, int action, int mods);

    /* ============================================================================
     * ---------------------------- GLFW_Cursorposfun
     * Cursor position callback function.
     * Called when the cursor moves within the window.
     *
     * ------ Parameters ------
     * window        The window that received the event.
     * xpos          The new cursor x-coordinate, relative to the window's client area.
     * ypos          The new cursor y-coordinate, relative to the window's client area.
     * ============================================================================
     */
    typedef void (*GLFW_Cursorposfun)(GLFWwindow* window, double xpos, double ypos);

    /* ============================================================================
     * ---------------------------- GLFW_Cursorenterfun
     * Cursor enter callback function.
     * Called when the cursor enters or leaves the window.
     *
     * ------ Parameters ------
     * window        The window that received the event.
     * entered       A boolean (1 for entered, 0 for left).
     * ============================================================================
     */
    typedef void (*GLFW_Cursorenterfun)(GLFWwindow* window, int entered);

    /* ============================================================================
     * ---------------------------- GLFW_Scrollfun
     * Scroll callback function.
     * Called when a scrolling device is used (e.g., mouse wheel).
     *
     * ------ Parameters ------
     * window        The window that received the event.
     * xoffset       The scroll offset along the x-axis.
     * yoffset       The scroll offset along the y-axis.
     * ============================================================================
     */
    typedef void (*GLFW_Scrollfun)(GLFWwindow* window, double xoffset, double yoffset);

    /* ============================================================================
     * ---------------------------- GLFW_Keyfun
     * Key callback function.
     * Called when a key is pressed, repeated, or released.
     *
     * ------ Parameters ------
     * window        The window that received the event.
     * key           The keyboard key that was pressed or released.
     * scancode      The system-specific scancode of the key.
     * action        The key action (e.g., GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT).
     * mods          Modifier keys (e.g., Shift, Control).
     * ============================================================================
     */
    typedef void (*GLFW_Keyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);

    /* ============================================================================
     * ---------------------------- GLFW_Charfun
     * Character callback function.
     * Called when a Unicode character is input.
     *
     * ------ Parameters ------
     * window        The window that received the event.
     * codepoint     The Unicode codepoint of the character.
     * ============================================================================
     */
    typedef void (*GLFW_Charfun)(GLFWwindow* window, unsigned int codepoint);

    /* ============================================================================
     * ---------------------------- GLFW_Charmodsfun
     * Character mods callback function.
     * Called when a Unicode character is input along with modifier keys.
     *
     * ------ Parameters ------
     * window        The window that received the event.
     * codepoint     The Unicode codepoint of the character.
     * mods          Modifier keys (e.g., Shift, Control).
     * ============================================================================
     */
    typedef void (*GLFW_Charmodsfun)(GLFWwindow* window, unsigned int codepoint, int mods);

    /* ============================================================================
     * ---------------------------- GLFW_Dropfun
     * Drop callback function.
     * Called when one or more files are dropped into the window.
     *
     * ------ Parameters ------
     * window        The window that received the drop event.
     * count         The number of dropped files.
     * paths         An array of UTF-8 encoded file paths.
     * ============================================================================
     */
    typedef void (*GLFW_Dropfun)(GLFWwindow* window, int count, const char** paths);

    /* ============================================================================
     * ---------------------------- GLFW_Joystickfun
     * Joystick callback function.
     * Called when a joystick is connected or disconnected.
     *
     * ------ Parameters ------
     * jid           The joystick ID (e.g., GLFW_JOYSTICK_1).
     * event         The connection event (e.g., GLFW_CONNECTED or GLFW_DISCONNECTED).
     * ============================================================================
     */
    typedef void (*GLFW_Joystickfun)(int jid, int event);

    /* ============================================================================
     * ---------------------------- callback_set_w Struct
     * Struct to hold pointers to all GLFW callback functions.
     * ============================================================================
     */
    typedef struct {
        GLFW_Errorfun               error_cb;
        GLFW_Windowposfun           window_pos_cb;
        GLFW_Windowsizefun          window_size_cb;
        GLFW_Windowclosefun         window_close_cb;
        GLFW_Windowrefreshfun       window_refresh_cb;
        GLFW_Windowfocusfun         window_focus_cb;
        GLFW_Windowiconifyfun       window_iconify_cb;
        GLFW_Windowmaximisefun      window_maximised_cb;
        GLFW_Framebuffersizefun     framebuffer_size_cb;
        GLFW_Windowcontentscalefun  content_scale_cb;
        GLFW_Mousebuttonfun         mouse_button_cb;
        GLFW_Cursorposfun           cursor_pos_cb;
        GLFW_Cursorenterfun         cursor_enter_cb;
        GLFW_Scrollfun              scroll_cb;
        GLFW_Keyfun                 key_cb;
        GLFW_Charfun                char_cb;
        GLFW_Charmodsfun            char_mods_cb;
        GLFW_Dropfun                drop_cb;
        GLFW_Joystickfun            joystick_cb;
    }glfw_cb_t;

    /* ============================================================================
     * ---------------------------- window_callbackset_t Struct
     * Struct to hold pointers to all window-related GLFW callback functions.
     * ============================================================================
     */
    typedef struct {
        GLFW_Windowposfun           window_pos_cb;
        GLFW_Windowsizefun          window_size_cb;
        GLFW_Windowclosefun         window_close_cb;
        GLFW_Windowrefreshfun       window_refresh_cb;
        GLFW_Windowfocusfun         window_focus_cb;
        GLFW_Windowiconifyfun       window_iconify_cb;
        GLFW_Windowmaximisefun      window_maximised_cb;
        GLFW_Framebuffersizefun     framebuffer_size_cb;
        GLFW_Windowcontentscalefun  content_scale_cb;
    }glfw_window_cb_t;

    /* ============================================================================
     * ---------------------------- glfw_input_callbackset_t Struct
     * Struct to hold pointers to all input-related GLFW callback functions.
     * ============================================================================
     */
    typedef struct {
        GLFW_Mousebuttonfun         mouse_button_cb;
        GLFW_Cursorposfun           cursor_pos_cb;
        GLFW_Cursorenterfun         cursor_enter_cb;
        GLFW_Scrollfun              scroll_cb;
        GLFW_Keyfun                 key_cb;
        GLFW_Charfun                char_cb;
        GLFW_Charmodsfun            char_mods_cb;
        GLFW_Dropfun                drop_cb;
        GLFW_Joystickfun            joystick_cb;
    }glfw_input_cb_t;
}
#endif // ! COIL_GLFW_CALLBACK_FUNCTION_FORMATS_H