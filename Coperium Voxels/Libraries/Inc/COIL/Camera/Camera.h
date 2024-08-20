#pragma once
#ifndef COIL_CAMERA_H
#define COIL_CAMERA_H
#include <GLM/glm.hpp>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <queue>

#include "../Utility.h"
#include "../Window/Window.h"


namespace Coil {

class Camera {
public:

    Camera(Window& window);
    Camera(Window& window, GLfloat Pos_x, GLfloat Pos_y, GLfloat Pos_z);

    // --------------------------------- Getters
    Window&     Get_Window              ()const;
    glm::vec3   Get_Position            ()const;
    glm::vec3   Get_Front               ()const;
    float       Get_FOV                 ()const;
    float       Get_Yaw                 ()const;
    float       Get_Pitch               ()const;
    float       Get_Movement_Speed      ()const;
    float       Get_Mouse_Sensitivity   ()const;

    // --------------------------------- Setters
    void        Set_Window              (const Window& window);
    void        Set_Position            (const glm::vec3& position);
    void        Set_Front               (const glm::vec3& front);
    void        Set_FOV                 (const float fov);
    void        Set_Yaw                 (const float yaw);
    void        Set_Pitch               (const float pitch);
    void        Set_Movement_Speed      (const float movement_speed);
    void        Set_Mouse_Sensitivity   (const float sensitivity);
    void        Set_Farplane            (const float far_plane);
    void        Set_Nearplane           (const float near_plane);
    void        Set_WindowWidth         (const int   window_width);
    void        Set_WindowHeight        (const int   window_height);



    virtual glm::mat4   Calc_View_Matrix       (                           ) = 0;
    virtual glm::mat4   Calc_Projection_Matrix (                           ) = 0;

    virtual void        Process_Keyboard       (float   deltaTime   ) = 0;
    virtual void        Process_Mouse_Movement (float   xoffset, 
                                                float   yoffset     ) = 0;
    virtual void        Process_Mouse_Scroll   (float   yoffset     ) = 0;
    virtual void        Process_Mouse_Button   (int     button, 
                                                int     action, 
                                                int     mods        ) = 0;

    virtual void        Update                 () = 0;

    
    virtual void        Take_Over_All_Input () = 0;
    virtual void        Take_Over_Mouse     () = 0;
    virtual void        Take_Over_Keyboard  () = 0;
    virtual void        Release_All_Input   () = 0;
    virtual void        Release_Mouse       () = 0;
    virtual void        Release_Keyboard    () = 0;

    ~Camera();
protected:

    // camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    // euler Angles
    float   yaw;
    float   pitch;
    float   movement_speed;
    float   mouse_sensitivity;
    float   fov;
    float   last_x;
    float   last_y;
    float   near_plane;
    float   far_plane;
    bool    first_mouse;
    int     window_width;
    int     window_height;
    Window& window;


    // Holds all possible Key presses
    std::unordered_map<int, key_states_t> key_map;

    // Updates some values based on the position Yaw Pitch etc... 
    void Update_Camera_Vectors();


    static void Mouse_Callback
        (GLFWwindow*    window,     double  xposIn, 
         double         yposIn);
    static void Keyboard_Callback
        (GLFWwindow*    window,     int     key, 
         int            scancode,   int     action,
         int            mods);
    static void Scroll_Callback
        (GLFWwindow*    window,     double  xoffset,
         double         yoffset);
    static void Button_Callback
        (GLFWwindow*    window,     int     button, 
         int            action,     int     mods);


    virtual void Window_Focus_Callback  (Window& window) = 0;
    virtual void Window_Size_Callback   (Window& window) = 0;
    static Camera*& Get_CurrentInstance ();
};


}
#endif // !COIL_CAMERA_H

