#include "ICpch.h"
#include "RenderFrame.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace ImguiCp {

    static void glfw_error_callback(int error, const char* description)
    {
        IC_CORE_ERROR("Glfw Error %d: %s\n", error, description);
    }

    GLFWwindow* RenderFrame::Create_glfw_Window(int width,int height,const char* title)
    {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit()) {
            IC_CORE_ERROR("glfw init failed!");
            return NULL;
        }
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL)
        {
            IC_CORE_ERROR("window init failed!");
            return NULL;
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            IC_CORE_ERROR("Failed to initialize GLAD");
            return NULL;
        }


        return window;
    }

    void RenderFrame::RenderMainImGui()
    {

    }
}