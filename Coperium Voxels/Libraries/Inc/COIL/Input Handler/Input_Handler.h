#pragma once
#ifndef COIL_INPUT_HANDLER_H
#define COIL_INPUT_HANDLER_H

#include "../Window/Window.h"

namespace Coil {

class Input_Handler{
public:
    Input_Handler(Window& window);
    void  Configure_CallBacks();

private:

    Window* window;

    static Input_Handler*& Current_Instance();
    void Focus_Handler(Window win);

    

    static void MouseButton_CB  (GLFWwindow* window, int button, int action, int mods);
    static void CursorPos_CB    (GLFWwindow* window, double xpos, double ypos);
    static void CursorEnter_CB  (GLFWwindow* window, int entered);
    static void Scroll_CB       (GLFWwindow* window, double xoffset, double yoffset);
    static void Key_CB          (GLFWwindow* window, int key, int scancode, int action, int mods);

    /* TODO 
    static void Char_CB         (GLFWwindow* window, unsigned int codepoint);
    static void CharMods_CB     (GLFWwindow* window, unsigned int codepoint, int mods);
    static void Drop_CB         (GLFWwindow* window, int count, const char** paths);
    static void Joystick_CB     (int jid, int event);
    */

};
}
#endif // !COIL_INPUT_HANDLER_H

