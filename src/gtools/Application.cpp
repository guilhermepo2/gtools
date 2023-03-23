#include "Application.h"
#include "Layer.h"
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow *window);

namespace gtools {
	// ==================================================================================
	Application::Application(const AppConfig& appConfig) {
		m_windowTitle = appConfig.WindowTitle;
		m_width = appConfig.width;
		m_height = appConfig.height;
	}

	// ==================================================================================
	void Application::Run() {
		Init();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		while (!glfwWindowShouldClose(m_window)) {
			processInput(m_window);

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// rendering
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Rendering our layers
			for (int i = 0; i < m_Layers.size(); i++) {
				m_Layers[i]->GUIRender();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// Update and Render additional Platform Windows
			// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
			//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}

		DeInit();
	}

	// ==================================================================================
	void Application::PushLayer(Layer* l) {
		m_Layers.push_back(l);
		l->OnAttach();
	}

	// ==================================================================================
	void Application::Init() {
		glfwInit();
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		m_window = glfwCreateWindow(m_width, m_height, m_windowTitle.c_str(), NULL, NULL);
		if (m_window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
		glfwSwapInterval(1); // Enable vsync

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad 
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	// ==================================================================================
	void Application::DeInit() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}

// ==================================================================================
// GLFW Handles
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}