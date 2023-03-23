//
// EntryPoint.h
//
#pragma once
#include "Application.h"

// to be defined on the client
extern Application* CreateApplication();

int main(int argc, char** argv) {
    Application* app = CreateApplication();

    if(app != nullptr) {
        app->Run();
        delete app;
    }

    return 0;
}