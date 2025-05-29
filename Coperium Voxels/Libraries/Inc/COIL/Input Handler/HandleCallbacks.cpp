#include "Input_Handler.h"

namespace Coil {


void Input_Handler::Key_CB(
    GLFWwindow* window, int key, int scancode, int action, int mods
){
    Input_Handler* input_handler = Current_Instance();

    if (input_handler != nullptr) {
        if (input_handler->previous_cb.key_cb   != nullptr  &&
            input_handler->allow_cb_chain       ==  true    ){

            input_handler->previous_cb.key_cb
                (window, key, scancode, action, mods);
        }

        key_event_t k;
        k.state = action == GLFW_PRESS ? io_states::PRESSED : io_states::UNPRESSED;

        for (const auto& callback : input_handler->key_cb_func) {
            /*TODO*/
        }
    }
}
void Input_Handler::MouseButton_CB(
    GLFWwindow* window, int button, int action, int mods
){
    Input_Handler* input_handler = Current_Instance();

    if (input_handler != nullptr) {
        if (input_handler->previous_cb.mouse_button_cb) {
        }
    }
}

void Input_Handler::CursorPos_CB(
    GLFWwindow* window, double xpos, double ypos
){

}

void Input_Handler::CursorEnter_CB(
    GLFWwindow* window, int entered
){

}

void Input_Handler::Scroll_CB(
    GLFWwindow* window, double xoffset, double yoffset
){

}

} // namespace Coil
