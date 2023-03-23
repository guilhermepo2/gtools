#include "gtools.h"

static bool g_showDemoWindow = true;

class MyLayer : public gtools::Layer {
public:
    void OnAttach() override {
        m_showDemoWindow = true;
    }

    void OnDettach() override {
        m_showDemoWindow = true;
    }

    void Update(float dt) override {}

    void GUIRender() {
        if (m_showDemoWindow) {
            ImGui::ShowDemoWindow(&m_showDemoWindow);
        }
    }

private:
    bool m_showDemoWindow;
};

gtools::Application* CreateApplication() {
    gtools::AppConfig conf;
    conf.WindowTitle = "TOOLS?";
    conf.width = 1024;
    conf.height = 768;

    gtools::Application* theApp = new gtools::Application(conf);
    theApp->PushLayer(new MyLayer());

    return theApp;
}