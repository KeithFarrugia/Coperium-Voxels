#include "Input_Handler.h"

namespace Coil {

    void Input_Handler::Add_Key_CallBack(
        const key_cb_t& callback
    ) {
        key_cb_func.push_back(callback);
    }
    void Input_Handler::Add_MouseMove_CallBack(
        const mouse_move_cb_t& callback
    ) {
        mouse_move_cb_func.push_back(callback);
    }
    void Input_Handler::Add_MouseClick_CallBack(
        const mouse_click_cb_t& callback
    ) {
        mouse_click_cb_func.push_back(callback);
    }
    void Input_Handler::Add_MouseScroll_CallBack(
        const mouse_scroll_cb_t& callback
    ) {

    }
}