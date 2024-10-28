#pragma once
#ifndef COIL_INPUT_ENUMS_H
#define COIL_INPUT_ENUMS_H

#include <functional>
#include <string>

namespace Coil {




typedef enum key_t {
    KEY_UNKNOWN         = -1,
    
    // Printable keys
    KEY_SPACE           = 32,   KEY_APOSTROPHE      = 39,
    KEY_COMMA           = 44,   KEY_MINUS           = 45,
    KEY_PERIOD          = 46,   KEY_SLASH           = 47,
    KEY_0               = 48,   KEY_1               = 49,
    KEY_2               = 50,   KEY_3               = 51,
    KEY_4               = 52,   KEY_5               = 53,
    KEY_6               = 54,   KEY_7               = 55,
    KEY_8               = 56,   KEY_9               = 57,
    KEY_SEMICOLON       = 59,   KEY_EQUAL           = 61,
    KEY_A               = 65,   KEY_B               = 66,
    KEY_C               = 67,   KEY_D               = 68,
    KEY_E               = 69,   KEY_F               = 70,
    KEY_G               = 71,   KEY_H               = 72,
    KEY_I               = 73,   KEY_J               = 74,
    KEY_K               = 75,   KEY_L               = 76,
    KEY_M               = 77,   KEY_N               = 78,
    KEY_O               = 79,   KEY_P               = 80,
    KEY_Q               = 81,   KEY_R               = 82,
    KEY_S               = 83,   KEY_T               = 84,
    KEY_U               = 85,   KEY_V               = 86,
    KEY_W               = 87,   KEY_X               = 88,
    KEY_Y               = 89,   KEY_Z               = 90,
    KEY_LEFT_BRACKET    = 91,   KEY_BACKSLASH       = 92,
    KEY_RIGHT_BRACKET   = 93,   KEY_GRAVE_ACCENT    = 96,
    KEY_WORLD_1         = 161,  KEY_WORLD_2         = 162,

    // Function keys
    KEY_ESCAPE          = 256,  KEY_ENTER           = 257,
    KEY_TAB             = 258,  KEY_BACKSPACE       = 259,
    KEY_INSERT          = 260,  KEY_DELETE          = 261,
    KEY_RIGHT           = 262,  KEY_LEFT            = 263,
    KEY_DOWN            = 264,  KEY_UP              = 265,
    KEY_PAGE_UP         = 266,  KEY_PAGE_DOWN       = 267,
    KEY_HOME            = 268,  KEY_END             = 269,
    KEY_CAPS_LOCK       = 280,  KEY_SCROLL_LOCK     = 281,
    KEY_NUM_LOCK        = 282,  KEY_PRINT_SCREEN    = 283,
    KEY_PAUSE           = 284,  KEY_F1              = 290,
    KEY_F2              = 291,  KEY_F3              = 292,
    KEY_F4              = 293,  KEY_F5              = 294,
    KEY_F6              = 295,  KEY_F7              = 296,
    KEY_F8              = 297,  KEY_F9              = 298,
    KEY_F10             = 299,  KEY_F11             = 300,
    KEY_F12             = 301,  KEY_F13             = 302,
    KEY_F14             = 303,  KEY_F15             = 304,
    KEY_F16             = 305,  KEY_F17             = 306,
    KEY_F18             = 307,  KEY_F19             = 308,
    KEY_F20             = 309,  KEY_F21             = 310,
    KEY_F22             = 311,  KEY_F23             = 312,
    KEY_F24             = 313,  KEY_F25             = 314,
    KEY_KP_0            = 320,  KEY_KP_1            = 321,
    KEY_KP_2            = 322,  KEY_KP_3            = 323,
    KEY_KP_4            = 324,  KEY_KP_5            = 325,
    KEY_KP_6            = 326,  KEY_KP_7            = 327,
    KEY_KP_8            = 328,  KEY_KP_9            = 329,
    KEY_KP_DECIMAL      = 330,  KEY_KP_DIVIDE       = 331,
    KEY_KP_MULTIPLY     = 332,  KEY_KP_SUBTRACT     = 333,
    KEY_KP_ADD          = 334,  KEY_KP_ENTER        = 335,
    KEY_KP_EQUAL        = 336,  KEY_LEFT_SHIFT      = 340,
    KEY_LEFT_CONTROL    = 341,  KEY_LEFT_ALT        = 342,
    KEY_LEFT_SUPER      = 343,  KEY_RIGHT_SHIFT     = 344,
    KEY_RIGHT_CONTROL   = 345,  KEY_RIGHT_ALT       = 346,
    KEY_RIGHT_SUPER     = 347,  KEY_MENU            = 348
} key_t;


typedef enum {
    HAT_CENTERED        = 0,    HAT_UP              = 1,
    HAT_RIGHT           = 2,    HAT_DOWN            = 4,
    HAT_LEFT            = 8,

    HAT_RIGHT_UP        = (HAT_RIGHT | HAT_UP),
    HAT_RIGHT_DOWN      = (HAT_RIGHT | HAT_DOWN),
    HAT_LEFT_UP         = (HAT_LEFT  | HAT_UP),
    HAT_LEFT_DOWN       = (HAT_LEFT  | HAT_DOWN)
} hat_state_t;

typedef enum {
    MOD_SHIFT           = 0x01, MOD_CONTROL         = 0x02,
    MOD_ALT             = 0x04, MOD_SUPER           = 0x08,
    MOD_CAPS_LOCK       = 0x10, MOD_NUM_LOCK        = 0x20
} mod_key_t;

typedef enum {
    MOUSE_BUTTON_1      = 0,    MOUSE_BUTTON_2      = 1,
    MOUSE_BUTTON_3      = 2,    MOUSE_BUTTON_4      = 3,
    MOUSE_BUTTON_5      = 4,    MOUSE_BUTTON_6      = 5,
    MOUSE_BUTTON_7      = 6,    MOUSE_BUTTON_8      = 7,

    MOUSE_BUTTON_LEFT   = MOUSE_BUTTON_1,
    MOUSE_BUTTON_RIGHT  = MOUSE_BUTTON_2,
    MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3
} mouse_button_t;

typedef enum {
    JOYSTICK_1          = 0,    JOYSTICK_2          = 1,
    JOYSTICK_3          = 2,    JOYSTICK_4          = 3,
    JOYSTICK_5          = 4,    JOYSTICK_6          = 5,
    JOYSTICK_7          = 6,    JOYSTICK_8          = 7,
    JOYSTICK_9          = 8,    JOYSTICK_10         = 9,
    JOYSTICK_11         = 10,   JOYSTICK_12         = 11,
    JOYSTICK_13         = 12,   JOYSTICK_14         = 13,
    JOYSTICK_15         = 14,   JOYSTICK_16         = 15
} joystick_t;

typedef enum {
    JOYSTICK_CONNECTED  = 0x00040001,
    JOYSTICK_DROPPED    = 0x00040002
} joystick_state_t;

typedef enum {
    GAMEPAD_A           = 0,    GAMEPAD_B           = 1,
    GAMEPAD_X           = 2,    GAMEPAD_Y           = 3,
    GAMEPAD_LB          = 4,    GAMEPAD_RB          = 5,
    GAMEPAD_BACK        = 6,    GAMEPAD_START       = 7,
    GAMEPAD_GUIDE       = 8,    GAMEPAD_LT          = 9,
    GAMEPAD_RT          = 10,   GAMEPAD_DPAD_UP     = 11,
    GAMEPAD_DPAD_RIGHT  = 12,   GAMEPAD_DPAD_DOWN   = 13,
    GAMEPAD_DPAD_LEFT   = 14,

    GAMEPAD_CROSS       = GAMEPAD_A,
    GAMEPAD_CIRCLE      = GAMEPAD_B,
    GAMEPAD_SQUARE      = GAMEPAD_X,
    GAMEPAD_TRIANGLE    = GAMEPAD_Y
} gamepad_button_t;


typedef enum {
    GAMEPAD_AX_LEFT_X   = 0,    GAMEPAD_AX_LEFT_Y   = 1,
    GAMEPAD_AX_RIGHT_X  = 2,    GAMEPAD_AX_RIGHT_Y  = 3,
    GAMEPAD_AX_LT       = 4,    GAMEPAD_AX_RT       = 5
} gamepad_axis_t;


typedef enum {
    REPEAT      ,
    PRESSED     ,
    UNPRESSED   ,

    CLICK   = PRESSED   ,
    UNCLICK = UNPRESSED ,
}io_states;

typedef enum {
    KEYBOARD,
    MOUSE_MOVEMENT,
    MOUSE_CLICK,
    MOUSE_SCROLL,

    JOYSTICK,
    GAMEPAD,
}io_type;

typedef struct {
    key_t       key;
    io_states   state;
}key_event_t;

typedef struct {
    bool    first_movement  ;
    double  prev_x          ;
    double  prev_y          ;
    double  new_x           ;
    double  new_y           ;
    double  offset_x        ;
    double  offset_y        ;
}mouse_move_event_t;

typedef struct {
    double  offset_x;
    double  offset_y;
}mouse_scroll_event_t;

typedef struct {
    mod_key_t       modifier;
    io_states       state   ;
    mouse_button_t  button  ;
}mouse_click_event_t;



key_t IntToKey(int key);
std::string KeyToString(key_t key);
std::string ModKeyToString(mod_key_t mod);
std::string MouseButtonToString(mouse_button_t button);
std::string JoystickToString(joystick_t joystick);
std::string JoystickStateToString(joystick_state_t state);
std::string GamepadButtonToString(gamepad_button_t button);

}

#endif // !COIL_INPUT_ENUMS_H
