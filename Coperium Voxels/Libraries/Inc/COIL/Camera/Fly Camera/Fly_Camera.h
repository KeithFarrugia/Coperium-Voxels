#pragma once
#ifndef COIL_FLY_CAMERA_H
#define COIL_FLY_CAMERA_H
#include "../Camera.h"

namespace Coil{
class Fly_Camera : public Camera {
public:

    Fly_Camera(Window& window);
    Fly_Camera(Window& window, GLfloat Pos_x, GLfloat Pos_y, GLfloat Pos_z);


    glm::mat4   Calc_View_Matrix       () override;
    glm::mat4   Calc_Projection_Matrix () override;

    void    Process_Keyboard       (float deltaTime ) override;
    void    Process_Mouse_Movement (float xoffset, 
                                    float yoffset   ) override;
    void    Process_Mouse_Scroll   (float yoffset   ) override;
    void    Process_Mouse_Button   (int   button, 
                                    int   action, 
                                    int   mods      ) override;

    void    Update                 () override;

    void    Take_Over_All_Input () override;
    void    Take_Over_Mouse     () override;
    void    Take_Over_Keyboard  () override;
    void    Release_All_Input   () override;
    void    Release_Mouse       () override;
    void    Release_Keyboard    () override;

    ~Fly_Camera() {  };

private:
    float last_frame;

    void Key_Handler            (int          key,
                                 io_states  event,
                                 float        velocity   );

    void Window_Focus_Callback  (Window& window);
    void Window_Size_Callback   (Window& window);

    bool toggle_mouse;

};
}
#endif // !COIL_FLY_CAMERA_H
