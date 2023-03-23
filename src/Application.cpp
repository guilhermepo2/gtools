#include "Application.h"
#include "Layer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


Application::Application(const AppConfig &appConfig) {
    m_windowTitle = appConfig.WindowTitle;
    m_width = appConfig.width;
    m_height = appConfig.height;
}

void Application::Run() {
    Init();
    // #todo
    // do the app loop
    Deinit();
}

void Application::PushLayer(Layer *l) {
    m_Layers.push_back(l);
    l->OnAttach();
}

void Application::Init() {
    // #todo
    // initialize window
    // initialize glad
    // initialize dearimgui
}

void Application::Deinit() {
    // shut everything down
}
