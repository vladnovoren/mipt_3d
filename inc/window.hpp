#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>

#include "load_shaders.hpp"

namespace rocgl {
  class Window {
   public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void SetClearColor(float red, float green, float blue, float alpha);

   private:
    GLWwindow* window = nullptr;
  };
}