#include "Input_Handler.h"
namespace Coil {

Input_Handler::Input_Handler(Window& window): window(&window){

}
/* ============================================================================
 * ---------------------------- Current_Instance
 * Returns a reference to the singleton instance of the Input_Handler class.
 *
 * ------ Returns ------
 * A reference to the singleton instance of the Input_Handler class.
 * ============================================================================
 */
Input_Handler*& Input_Handler::Current_Instance() {
    static Input_Handler* instance = nullptr;
    return instance;
}


void Input_Handler::Focus_Handler(Window win){
    if (window->Is_Focused()) {
        Current_Instance() = this;
    }
}


void Input_Handler::Configure_CallBacks() {
    /*previous_cb.mouse_button_cb = SetCallback(previous_cb.mouse_button_cb,
        MouseButton_CB, glfwSetMouseButtonCallback);

    previous_cb.cursor_pos_cb = SetCallback(previous_cb.cursor_pos_cb,
        CursorPos_CB, glfwSetCursorPosCallback);

    previous_cb.cursor_enter_cb = SetCallback(previous_cb.cursor_enter_cb,
        CursorEnter_CB, glfwSetCursorEnterCallback);

    previous_cb.scroll_cb = SetCallback(previous_cb.scroll_cb,
        Scroll_CB, glfwSetScrollCallback);

    previous_cb.key_cb = SetCallback(previous_cb.key_cb,
        Key_CB, glfwSetKeyCallback);

    previous_cb.char_cb = SetCallback(previous_cb.char_cb,
        Char_CB, glfwSetCharCallback);

    previous_cb.char_mods_cb = SetCallback(previous_cb.char_mods_cb,
        CharMods_CB, glfwSetCharModsCallback);

    previous_cb.drop_cb = SetCallback(previous_cb.drop_cb,
        Drop_CB, glfwSetDropCallback);

    previous_cb.joystick_cb = SetCallback(previous_cb.joystick_cb,
        Joystick_CB, glfwSetJoystickCallback);*/
}
}