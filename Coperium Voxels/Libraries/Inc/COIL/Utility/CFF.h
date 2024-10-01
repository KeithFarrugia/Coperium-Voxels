#pragma once
#ifndef COIL_CALLBACK_FUNCTION_FORMATS_H
#define COIL_CALLBACK_FUNCTION_FORMATS_H

// --------------------------------- External Includes
#include <functional>

// --------------------------------- Internal Includes
#include "IO.h"

namespace Coil {
    class Window;

    /* ============================================================================
     * ---------------------------- window_cb_t Type
     * Defines a short type alias for a callback function that takes a reference
     * to a Window and returns void.
     * ============================================================================
     */
    typedef std::function<void(Window&)> window_cb_t;

    /* ============================================================================
     * ---------------------------- key_cb_t Type
     * Defines a type alias for a callback function that takes a reference to
     * a key_event_t structure and returns void. This is used for handling key
     * events such as key presses and releases.
     * ============================================================================
     */
    typedef std::function<void(key_event_t&)> key_cb_t;

    /* ============================================================================
     * ---------------------------- mouse_move_cb_t Type
     * Defines a type alias for a callback function that takes a reference to
     * a mouse_move_event_t structure and returns void. This is used for handling
     * mouse movement events.
     * ============================================================================
     */
    typedef std::function<void(mouse_move_event_t&)> mouse_move_cb_t;

    /* ============================================================================
     * ---------------------------- mouse_click_cb_t Type
     * Defines a type alias for a callback function that takes a reference to
     * a mouse_click_event_t structure and returns void. This is used for handling
     * mouse click events, such as button presses and releases.
     * ============================================================================
     */
    typedef std::function<void(mouse_click_event_t&)> mouse_click_cb_t;

    /* ============================================================================
     * ---------------------------- mouse_scroll_cb_t Type
     * Defines a type alias for a callback function that takes a reference to
     * a mouse_scroll_event_t structure and returns void. This is used for handling
     * mouse scroll events, such as scrolling with a mouse wheel or trackpad.
     * ============================================================================
     */
    typedef std::function<void(mouse_scroll_event_t&)> mouse_scroll_cb_t;



    typedef struct {
        key_cb_t func;
        std::string command_name;
    }key_command_t;

    typedef struct {
        mouse_move_cb_t func;
        std::string command_name;
    }mouse_move_command_t;

    typedef struct {
        mouse_click_cb_t func;
        std::string command_name;
    }mouse_click_command_t;

    typedef struct {
        mouse_scroll_cb_t func;
        std::string command_name;
    }mouse_scroll_command_t;


}

#endif // !COIL_CALLBACK_FUNCTION_FORMATS_H
