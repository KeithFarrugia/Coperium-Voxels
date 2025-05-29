#pragma once
#ifndef COIL_INPUT_HANDLER_H
#define COIL_INPUT_HANDLER_H

#include "../Window/Window.h"
#include "../Utility.h"

namespace Coil {

class Input_Handler{
public:
    Input_Handler(Window& window);

    void Add_Key_CallBack
        (const key_cb_t&            callback);
    void Add_MouseMove_CallBack
        (const mouse_move_cb_t&     callback);
    void Add_MouseClick_CallBack
        (const mouse_click_cb_t&    callback);
    void Add_MouseScroll_CallBack
        (const mouse_scroll_cb_t&   callback);


private:

    Window* window;
    glfw_input_cb_t previous_cb;
    bool allow_cb_chain;
    std::vector<key_cb_t>           key_cb_func;
    std::vector<mouse_move_cb_t>    mouse_move_cb_func;
    std::vector<mouse_click_cb_t>   mouse_click_cb_func;
    std::vector<mouse_scroll_cb_t>  mouse_scroll_cb_func;

    void  Configure_CallBacks();

    static Input_Handler*& Current_Instance();
    void Focus_Handler(Window win);

    

    template<typename cb_t>
    cb_t SetCallback(cb_t& previous, cb_t newCallback, cb_t(*setFunction)(GLFWwindow*, cb_t));

    static void MouseButton_CB  (GLFWwindow* window, int    button, int action, int mods);
    static void CursorPos_CB    (GLFWwindow* window, double xpos,   double ypos);
    static void CursorEnter_CB  (GLFWwindow* window, int    entered);
    static void Scroll_CB       (GLFWwindow* window, double xoffset,double yoffset);
    static void Key_CB          (GLFWwindow* window, int    key, int scancode, int action, int mods);

    /* TODO 
    static void Char_CB         (GLFWwindow* window, unsigned int codepoint);
    static void CharMods_CB     (GLFWwindow* window, unsigned int codepoint, int mods);
    static void Drop_CB         (GLFWwindow* window, int count, const char** paths);
    static void Joystick_CB     (int jid, int event);
    */

};
}
#endif // !COIL_INPUT_HANDLER_H

