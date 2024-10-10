#include "IO.h"

namespace Coil{

inline int KeyToInt(key_t key) {
    return static_cast<int>(key);
}

key_t IntToKey(int key) {
    switch (key) {
        case -1     :return KEY_UNKNOWN;        case 32     :return KEY_SPACE;
        case 39     :return KEY_APOSTROPHE;     case 44     :return KEY_COMMA;
        case 45     :return KEY_MINUS;          case 46     :return KEY_PERIOD;
        case 47     :return KEY_SLASH;          case 48     :return KEY_0;
        case 49     :return KEY_1;              case 50     :return KEY_2;
        case 51     :return KEY_3;              case 52     :return KEY_4;
        case 53     :return KEY_5;              case 54     :return KEY_6;
        case 55     :return KEY_7;              case 56     :return KEY_8;
        case 57     :return KEY_9;              case 59     :return KEY_SEMICOLON;
        case 61     :return KEY_EQUAL;          case 65     :return KEY_A;
        case 66     :return KEY_B;              case 67     :return KEY_C;
        case 68     :return KEY_D;              case 69     :return KEY_E;
        case 70     :return KEY_F;              case 71     :return KEY_G;
        case 72     :return KEY_H;              case 73     :return KEY_I;
        case 74     :return KEY_J;              case 75     :return KEY_K;
        case 76     :return KEY_L;              case 77     :return KEY_M;
        case 78     :return KEY_N;              case 79     :return KEY_O;
        case 80     :return KEY_P;              case 81     :return KEY_Q;
        case 82     :return KEY_R;              case 83     :return KEY_S;
        case 84     :return KEY_T;              case 85     :return KEY_U;
        case 86     :return KEY_V;              case 87     :return KEY_W;
        case 88     :return KEY_X;              case 89     :return KEY_Y;
        case 90     :return KEY_Z;              case 91     :return KEY_LEFT_BRACKET;
        case 92     :return KEY_BACKSLASH;      case 93     :return KEY_RIGHT_BRACKET;
        case 96     :return KEY_GRAVE_ACCENT;   case 161    :return KEY_WORLD_1;
        case 162    :return KEY_WORLD_2;

        // Function keys
        case 256    :return KEY_ESCAPE;         case 257    :return KEY_ENTER;
        case 258    :return KEY_TAB;            case 259    :return KEY_BACKSPACE;
        case 260    :return KEY_INSERT;         case 261    :return KEY_DELETE;
        case 262    :return KEY_RIGHT;          case 263    :return KEY_LEFT;
        case 264    :return KEY_DOWN;           case 265    :return KEY_UP;
        case 266    :return KEY_PAGE_UP;        case 267    :return KEY_PAGE_DOWN;
        case 268    :return KEY_HOME;           case 269    :return KEY_END;
        case 280    :return KEY_CAPS_LOCK;      case 281    :return KEY_SCROLL_LOCK;
        case 282    :return KEY_NUM_LOCK;       case 283    :return KEY_PRINT_SCREEN;
        case 284    :return KEY_PAUSE;          case 290    :return KEY_F1;
        case 291    :return KEY_F2;             case 292    :return KEY_F3;
        case 293    :return KEY_F4;             case 294    :return KEY_F5;
        case 295    :return KEY_F6;             case 296    :return KEY_F7;
        case 297    :return KEY_F8;             case 298    :return KEY_F9;
        case 299    :return KEY_F10;            case 300    :return KEY_F11;
        case 301    :return KEY_F12;            case 302    :return KEY_F13;
        case 303    :return KEY_F14;            case 304    :return KEY_F15;
        case 305    :return KEY_F16;            case 306    :return KEY_F17;
        case 307    :return KEY_F18;            case 308    :return KEY_F19;
        case 309    :return KEY_F20;            case 310    :return KEY_F21;
        case 311    :return KEY_F22;            case 312    :return KEY_F23;
        case 313    :return KEY_F24;            case 314    :return KEY_F25;

        // Keypad keys
        case 320    :return KEY_KP_0;           case 321    :return KEY_KP_1;
        case 322    :return KEY_KP_2;           case 323    :return KEY_KP_3;
        case 324    :return KEY_KP_4;           case 325    :return KEY_KP_5;
        case 326    :return KEY_KP_6;           case 327    :return KEY_KP_7;
        case 328    :return KEY_KP_8;           case 329    :return KEY_KP_9;
        case 330    :return KEY_KP_DECIMAL;     case 331    :return KEY_KP_DIVIDE;
        case 332    :return KEY_KP_MULTIPLY;    case 333    :return KEY_KP_SUBTRACT;
        case 334    :return KEY_KP_ADD;         case 335    :return KEY_KP_ENTER;
        case 336    :return KEY_KP_EQUAL;

        // Modifier keys
        case 340    :return KEY_LEFT_SHIFT;     case 341    :return KEY_LEFT_CONTROL;
        case 342    :return KEY_LEFT_ALT;       case 343    :return KEY_LEFT_SUPER;
        case 344    :return KEY_RIGHT_SHIFT;    case 345    :return KEY_RIGHT_CONTROL;
        case 346    :return KEY_RIGHT_ALT;      case 347    :return KEY_RIGHT_SUPER;
        case 348    :return KEY_MENU;

        default     :KEY_UNKNOWN;
    }
}
std::string KeyToString(key_t key) {
    switch (key) {
    case KEY_UNKNOWN        :return "Unknown";      case KEY_SPACE          :return " ";
    case KEY_APOSTROPHE     :return "'";            case KEY_COMMA          :return ",";
    case KEY_MINUS          :return "-";            case KEY_PERIOD         :return ".";
    case KEY_SLASH          :return "/";            case KEY_0              :return "0";
    case KEY_1              :return "1";            case KEY_2              :return "2";
    case KEY_3              :return "3";            case KEY_4              :return "4";
    case KEY_5              :return "5";            case KEY_6              :return "6";
    case KEY_7              :return "7";            case KEY_8              :return "8";
    case KEY_9              :return "9";            case KEY_SEMICOLON      :return ";";
    case KEY_EQUAL          :return "=";            case KEY_A              :return "A";
    case KEY_B              :return "B";            case KEY_C              :return "C";
    case KEY_D              :return "D";            case KEY_E              :return "E";
    case KEY_F              :return "F";            case KEY_G              :return "G";
    case KEY_H              :return "H";            case KEY_I              :return "I";
    case KEY_J              :return "J";            case KEY_K              :return "K";
    case KEY_L              :return "L";            case KEY_M              :return "M";
    case KEY_N              :return "N";            case KEY_O              :return "O";
    case KEY_P              :return "P";            case KEY_Q              :return "Q";
    case KEY_R              :return "R";            case KEY_S              :return "S";
    case KEY_T              :return "T";            case KEY_U              :return "U";
    case KEY_V              :return "V";            case KEY_W              :return "W";
    case KEY_X              :return "X";            case KEY_Y              :return "Y";
    case KEY_Z              :return "Z";            case KEY_LEFT_BRACKET   :return "[";
    case KEY_BACKSLASH      :return "\\";           case KEY_RIGHT_BRACKET  :return "]";
    case KEY_GRAVE_ACCENT   :return "`";            case KEY_WORLD_1        :return "World 1";
    case KEY_WORLD_2        :return "World 2";

    // Function keys
    case KEY_ESCAPE         :return "Esc";          case KEY_ENTER          :return "Enter";
    case KEY_TAB            :return "Tab";          case KEY_BACKSPACE      :return "Backspace";
    case KEY_INSERT         :return "Insert";       case KEY_DELETE         :return "Delete";
    case KEY_RIGHT          :return "Right";        case KEY_LEFT           :return "Left";
    case KEY_DOWN           :return "Down";         case KEY_UP             :return "Up";
    case KEY_PAGE_UP        :return "Page Up";      case KEY_PAGE_DOWN      :return "Page Down";
    case KEY_HOME           :return "Home";         case KEY_END            :return "End";
    case KEY_CAPS_LOCK      :return "Caps Lock";    case KEY_SCROLL_LOCK    :return "Scroll Lock";
    case KEY_NUM_LOCK       :return "Num Lock";     case KEY_PRINT_SCREEN   :return "Print Screen";
    case KEY_PAUSE          :return "Pause";        case KEY_F1             :return "F1";
    case KEY_F2             :return "F2";           case KEY_F3             :return "F3";
    case KEY_F4             :return "F4";           case KEY_F5             :return "F5";
    case KEY_F6             :return "F6";           case KEY_F7             :return "F7";
    case KEY_F8             :return "F8";           case KEY_F9             :return "F9";
    case KEY_F10            :return "F10";          case KEY_F11            :return "F11";
    case KEY_F12            :return "F12";          case KEY_F13            :return "F13";
    case KEY_F14            :return "F14";          case KEY_F15            :return "F15";
    case KEY_F16            :return "F16";          case KEY_F17            :return "F17";
    case KEY_F18            :return "F18";          case KEY_F19            :return "F19";
    case KEY_F20            :return "F20";          case KEY_F21            :return "F21";
    case KEY_F22            :return "F22";          case KEY_F23            :return "F23";
    case KEY_F24            :return "F24";          case KEY_F25            :return "F25";

    // Keypad keys
    case KEY_KP_0           :return "KP 0";         case KEY_KP_1           :return "KP 1";
    case KEY_KP_2           :return "KP 2";         case KEY_KP_3           :return "KP 3";
    case KEY_KP_4           :return "KP 4";         case KEY_KP_5           :return "KP 5";
    case KEY_KP_6           :return "KP 6";         case KEY_KP_7           :return "KP 7";
    case KEY_KP_8           :return "KP 8";         case KEY_KP_9           :return "KP 9";
    case KEY_KP_DECIMAL     :return "KP .";         case KEY_KP_DIVIDE      :return "KP /";
    case KEY_KP_MULTIPLY    :return "KP *";         case KEY_KP_SUBTRACT    :return "KP -";
    case KEY_KP_ADD         :return "KP +";         case KEY_KP_ENTER       :return "KP Enter";
    case KEY_KP_EQUAL       :return "KP =";

    // Modifier keys
    case KEY_LEFT_SHIFT     :return "Left Shift";   case KEY_LEFT_CONTROL   :return "Left Ctrl";
    case KEY_LEFT_ALT       :return "Left Alt";     case KEY_LEFT_SUPER     :return "Left Super";
    case KEY_RIGHT_SHIFT    :return "Right Shift";  case KEY_RIGHT_CONTROL  :return "Right Ctrl";
    case KEY_RIGHT_ALT      :return "Right Alt";    case KEY_RIGHT_SUPER    :return "Right Super";
    case KEY_MENU           :return "Menu";

    default:return "Unknown";
    }
}



int HatStateToInt(hat_state_t hat) {
    return static_cast<int>(hat);
}

hat_state_t IntToHatState(int value) {
    switch (value) {
    case 0  :return HAT_CENTERED;   case 1  :return HAT_UP;
    case 2  :return HAT_RIGHT;      case 4  :return HAT_DOWN;
    case 8  :return HAT_LEFT;       case 3  :return HAT_RIGHT_UP;     
    case 6  :return HAT_RIGHT_DOWN; case 9  :return HAT_LEFT_UP;
    case 12 :return HAT_LEFT_DOWN;  default :return HAT_CENTERED;
    }
}

std::string HatStateToString(hat_state_t hat) {
    switch (hat) {
    case HAT_CENTERED   :return "Centered";     case HAT_UP         :return "Up";
    case HAT_RIGHT      :return "Right";        case HAT_DOWN       :return "Down";
    case HAT_LEFT       :return "Left";         case HAT_RIGHT_UP   :return "Right-Up";
    case HAT_RIGHT_DOWN :return "Right-Down";   case HAT_LEFT_UP    :return "Left-Up";
    case HAT_LEFT_DOWN  :return "Left-Down";    default             :return "Unknown hat state";
    }
}


std::string ModKeyToString(mod_key_t mod) {
    switch (mod) {
    case MOD_SHIFT         :return "Shift";             case MOD_CONTROL    :return "Ctrl";
    case MOD_ALT           :return "Alt";               case MOD_SUPER      :return "Super";
    case MOD_CAPS_LOCK     :return "Caps Lock";         case MOD_NUM_LOCK   :return "Num Lock";
    default                :return "Unknown modifier";
    }
}

std::string MouseButtonToString(mouse_button_t button) {
    switch (button) {
    case MOUSE_BUTTON_1     : return "Left Button";
    case MOUSE_BUTTON_2     : return "Right Button";
    case MOUSE_BUTTON_3     : return "Middle Button";
    case MOUSE_BUTTON_4     : return "Button 4";
    case MOUSE_BUTTON_5     : return "Button 5";
    case MOUSE_BUTTON_6     : return "Button 6";
    case MOUSE_BUTTON_7     : return "Button 7";
    case MOUSE_BUTTON_8     : return "Button 8";
    default                 : return "Unknown mouse button";
    }
}

std::string JoystickToString(joystick_t joystick) {
    switch (joystick) {
    case JOYSTICK_1         : return "Joystick 1";
    case JOYSTICK_2         : return "Joystick 2";
    case JOYSTICK_3         : return "Joystick 3";
    case JOYSTICK_4         : return "Joystick 4";
    case JOYSTICK_5         : return "Joystick 5";
    case JOYSTICK_6         : return "Joystick 6";
    case JOYSTICK_7         : return "Joystick 7";
    case JOYSTICK_8         : return "Joystick 8";
    case JOYSTICK_9         : return "Joystick 9";
    case JOYSTICK_10        : return "Joystick 10";
    case JOYSTICK_11        : return "Joystick 11";
    case JOYSTICK_12        : return "Joystick 12";
    case JOYSTICK_13        : return "Joystick 13";
    case JOYSTICK_14        : return "Joystick 14";
    case JOYSTICK_15        : return "Joystick 15";
    case JOYSTICK_16        : return "Joystick 16";
    default                 : return "Unknown joystick";
    }
}

std::string JoystickStateToString(joystick_state_t state) {
    switch (state) {
    case JOYSTICK_CONNECTED : return "Joystick Connected";
    case JOYSTICK_DROPPED   : return "Joystick Dropped";
    default                 : return "Unknown joystick state";
    }
}

std::string GamepadButtonToString(gamepad_button_t button) {
    switch (button) {
    case GAMEPAD_A          : return "A / Cross";
    case GAMEPAD_B          : return "B / Circle";
    case GAMEPAD_X          : return "X / Square";
    case GAMEPAD_Y          : return "Y / Triangle";
    case GAMEPAD_LB         : return "Left Bumper";
    case GAMEPAD_RB         : return "Right Bumper";
    case GAMEPAD_BACK       : return "Back";
    case GAMEPAD_START      : return "Start";
    case GAMEPAD_GUIDE      : return "Guide";
    case GAMEPAD_LT         : return "Left Trigger";
    case GAMEPAD_RT         : return "Right Trigger";
    case GAMEPAD_DPAD_UP    : return "D-pad Up";
    case GAMEPAD_DPAD_RIGHT : return "D-pad Right";
    case GAMEPAD_DPAD_DOWN  : return "D-pad Down";
    case GAMEPAD_DPAD_LEFT  : return "D-pad Left";
    default                 : return "Unknown gamepad button";
    }
}
}