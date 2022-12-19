#include "window.hpp"

namespace rocgl {
  Window::Window(int width, int height, const std::string& name) {
    if (!glfwInit()) {
      throw std::runtime_error("unable to init GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1024, 720, "Triangles", NULL, NULL);
    if (window == nullptr) {
      throw std::runtime_error("unable to open window");
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
      throw std::runtime_error("unable to init glew");
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  }

  void Window::SetClearColor(float red, float green, float blue, float alpha) {
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  }

  Window::~Window() {

  }
}