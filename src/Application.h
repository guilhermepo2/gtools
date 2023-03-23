//
// Application.h
//

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

#pragma once
class Layer;

struct AppConfig {
    std::string WindowTitle = "Test";
    int width = 960;
    int height = 540;
};

class Application {
public:
    Application(const AppConfig& appConfig);
    void Run();
    void PushLayer(Layer* l);

private:
    void Init();
    void Deinit();
private:
    std::string m_windowTitle;
    int m_width;
    int m_height;

    GLFWwindow* m_window;
    bool m_isRunning;
    std::vector<Layer*> m_Layers;
};