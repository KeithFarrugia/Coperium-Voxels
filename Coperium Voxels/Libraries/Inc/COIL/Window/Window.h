#pragma once
#ifndef COIL_WINDOW_H
#define COIL_WINDOW_H

// --------------------------------- External Includes
#include <GLAD/glad.h>
#include <functional>
#include <vector>
#include <mutex>

// --------------------------------- Internal Includes
#include "../Utility.h"


namespace Coil{

    
class Window{
public:
    Window();
    Window( const std::string name,
            const int w, const int h);
    ~Window();

    // --------------------------------- Basic Functions
    void Del                ();
    void Show               ();
    void Hide               ();
    void Iconify            ();
    void Restore            ();
    void Maximise           ();
    void Focus              ();
    void RequestAttention   ();
    void SwapBuffers        ();
    void EnableVsync        ();
    void DisableVsync       ();
    void EnableDepthTest    ();
    void DisableDepthTest   ();
    void EnableCulling      ();
    void DisableCulling     ();
    void FF_Clockwise       ();
    void FF_UntiClockwise   ();
    void FullScreen         ();
    void Windowed           ();

    Window* MakeContext     ();
    Window* MakeContext     (Window*);

    void Configure_CallBacks();
    // --------------------------------- Queiries
    bool Is_FullScreen      () const;
    bool Does_Exist         () const;
    bool Is_Visible         () const;
    bool Is_Iconified       () const;
    bool Is_Maximised       () const;
    bool Is_Focused         () const;
    bool Is_Resizable       () const;
    bool Is_Decorated       () const;
    bool Is_Closed          () const;

    // --------------------------------- Setters
    void Set_Title          (const std::string title);
    void Set_Icon           (const std::vector<GLFWimage>& images);
    void Set_Position       (const int x,       const int y);
    void Set_Size           (const int w,       const int h);

    void Set_SizeLimit      (const int min_w,   const int min_h,
                             const int max_w,   const int max_h);

    void Set_AspectRatio    (const int n,       const int d);

    void Set_Monitor        (GLFWmonitor* monitor, 
                             const int x,       const int y, 
                             const int w,       const int h, 
                             const int refreshRate);

    void Set_Attribute      (const int attrib, const int value);
    void Set_Resizable      (const bool resizable);
    void Set_Decorated      (const bool decorated);

    void Allow_CB_Chain     (const bool allow_chain);

    // --------------------------------- Getters
    GLFWwindow* Get_Window  ();

    void Get_Position       (int&   x,          int& y          ) const;
    void Get_Size           (int&   w,          int& h          ) const;
    void Get_FrameBufferSize(int&   w,          int& h          ) const;
    void Get_FrameSize      (int&   l,          int& r, 
                             int&   t,          int& b          ) const;

    void Get_ContentScale   (float& x_scale,    float& y_scale  ) const;
    void Get_Opacity        (float& o                           ) const;

    void Get_Monitor        (GLFWmonitor** monitor              ) const;

    void Get_Attribute      (const int attrib,  int& result     ) const;
    void Get_RefreshRate    (int& rf                            ) const;


    // --------------------------------- Add Call Back Handlers
    void Add_Size_Callback
        (const window_cb_t& callback);
    void Add_Frame_Callback
        (const window_cb_t& callback);
    void Add_Close_Callback
        (const window_cb_t& callback);
    void Add_Refresh_Callback
        (const window_cb_t& callback);
    void Add_Focus_Callback
        (const window_cb_t& callback);
    void Add_Iconify_Callback
        (const window_cb_t& callback);
    void Add_Maximise_Callback
        (const window_cb_t& callback);
    void Add_Position_Callback
        (const window_cb_t& callback);
    void Add_Content_Scale_Callback
        (const window_cb_t& callback);

    
private:
    GLFWwindow* window;
    int     windowed_x, windowed_y;
    int     windowed_w, windowed_h;

    bool    allow_cb_chain;
    
    static Window* current_context;
    std::mutex w_mt;

    // --------------------------------- Call Back Handlers Lists
    std::vector<window_cb_t> size_cf     ;
    std::vector<window_cb_t> frame_cf    ;
    std::vector<window_cb_t> close_cf    ;
    std::vector<window_cb_t> refresh_cf  ;
    std::vector<window_cb_t> focus_cf    ;
    std::vector<window_cb_t> iconify_cf  ;
    std::vector<window_cb_t> maximise_cf ;
    std::vector<window_cb_t> position_cf ;
    std::vector<window_cb_t> content_cf  ;

    glfw_window_cb_t previous_cb;

    // --------------------------------- Call Back Handlers
    static void Window_Refresh_CB
        (GLFWwindow* win                                );
    static void Window_Close_CB
        (GLFWwindow* win                                );
    static void Window_Focus_CB
        (GLFWwindow* win, int   focused                 );
    static void Window_Iconify_CB
        (GLFWwindow* win, int   iconified               );
    static void Window_Maximise_CB
        (GLFWwindow* win, int   maximized               );
    static void Window_Size_CB
        (GLFWwindow* win, int   width,  int     height  );
    static void Window_Framebuffer_Size_CB
        (GLFWwindow* win, int   width,  int     height  );
    static void Window_Pos_CB
        (GLFWwindow* win, int   xpos,   int     ypos    );
    static void Window_Content_Scale_CB
        (GLFWwindow* win, float xscale, float   yscale  );

    template<typename cb_t>
    cb_t SetCallback(   cb_t& previous, cb_t newCallback,
                        cb_t(*setFunction)(GLFWwindow*, cb_t));

};


}

#endif // !COIL_WINDOW_H