#include "Window.h"

namespace Coil {

/* ============================================================================
 * ---------------------------- Add Size Callback
 * Registers a callback function to be called when the window is resized.
 * The function will be added to the list of size callback functions.
 * 
 * ------ Parameters ------
 * callback: The callback function to be registered. It takes a reference 
 *           to a Window object as its parameter.
 * ============================================================================
 */
void Window::Add_Size_Callback(
    const std::function<void(Window&)>& callback
){
    size_cf.push_back(callback);
}

/* ============================================================================
 * --------------------------- Add Frame Callback
 * Registers a callback function to be called when the framebuffer is resized.
 * The function will be added to the list of frame callback functions.
 * 
 * ------ Parameters ------
 * callback: The callback function to be registered. It takes a reference 
 *           to a Window object as its parameter.
 * ============================================================================
 */
void Window::Add_Frame_Callback(
    const std::function<void(Window&)>& callback
){
    frame_cf.push_back(callback);
}

/* ============================================================================
 * ---------------------------- Add Close Callback
 * Registers a callback function to be called when the window is about to close.
 * The function will be added to the list of close callback functions.
 * 
 * ------ Parameters ------
 * callback: The callback function to be registered. It takes a reference 
 *           to a Window object as its parameter.
 * ============================================================================
 */
void Window::Add_Close_Callback(
    const std::function<void(Window&)>& callback
){
    close_cf.push_back(callback);
}

/* ============================================================================
 * -------------------------- Add Refresh Callback
 * Registers a callback function to be called when the window needs to be redrawn.
 * The function will be added to the list of refresh callback functions.
 * 
 * ------ Parameters ------
 * callback: The callback function to be registered. It takes a reference 
 *           to a Window object as its parameter.
 * ============================================================================
 */
void Window::Add_Refresh_Callback(
    const std::function<void(Window&)>& callback
){
    refresh_cf.push_back(callback);
}

/* ============================================================================
 * --------------------------- Add Focus Callback
 * Registers a callback function to be called when the window gains or loses focus.
 * The function will be added to the list of focus callback functions.
 * 
 * ------ Parameters ------
 * callback: The callback function to be registered. It takes a reference 
 *           to a Window object as its parameter.
 * ============================================================================
 */
void Window::Add_Focus_Callback(
    const std::function<void(Window&)>& callback
){
    focus_cf.push_back(callback);
}

/* ============================================================================
 * -------------------------- Add Iconify Callback
 * Registers a callback function to be called when the window is minimized or restored.
 * The function will be added to the list of iconify callback functions.
 * 
 * ------ Parameters ------
 * callback: The callback function to be registered. It takes a reference 
 *           to a Window object as its parameter.
 * ============================================================================
 */
void Window::Add_Iconify_Callback(
    const std::function<void(Window&)>& callback
){
    iconify_cf.push_back(callback);
}

/* ============================================================================
 * -------------------------- Add Position Callback
 * Registers a callback function to be called when the window is moved.
 * The function will be added to the list of position callback functions.
 * 
 * ------ Parameters ------
 * callback: The callback function to be registered. It takes a reference 
 *           to a Window object as its parameter.
 * ============================================================================
 */
void Window::Add_Position_Callback(
    const std::function<void(Window&)>& callback
){
    position_cf.push_back(callback);
}

/* ============================================================================
 * ---------------------- Add Content Scale Callback
 * Registers a callback function to be called when the content scale of the 
 * window changes, such as when moved between monitors with different DPI settings.
 * The function will be added to the list of content scale callback functions.
 * 
 * ------ Parameters ------
 * callback: The callback function to be registered. It takes a reference 
 *           to a Window object as its parameter.
 * ============================================================================
 */
void Window::Add_Content_Scale_Callback(
    const std::function<void(Window&)>& callback
){
    content_cf.push_back(callback);
}

} // namespace Coil
