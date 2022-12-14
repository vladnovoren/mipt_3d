#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "load_shaders.hpp"

using namespace glm;

struct Vertex
{
  glm::vec3 position;
  glm::vec4 color;
};

int main() {
  if (!glfwInit()) {
      fprintf( stderr, "unable to init GLFW\n" );
      return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window;
  window = glfwCreateWindow(1024, 768, "Triangles", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "unable to open window\n");
    return -1;
  }
  glfwMakeContextCurrent(window);

  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "unable to init glew\n");
    return -1;
  }

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);

  GLuint programID = LoadShaders("../shaders/vertex_shader.vertexshader",
                                 "../shaders/fragment_shader.fragmentshader");

  GLuint view_id = glGetUniformLocation(programID, "V");
  GLuint projection_id = glGetUniformLocation(programID, "P");

  glm::mat4 view;
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

//  static const Vertex vertices[] = {
//      {{-1.0f, -1.0f, -1.0f}, {0.0, 0.0, 0.5, 0.5}},
//      {{1.0f, -1.0f, 1.0f}, {0.0, 0.0, 0.5, 0.5}},
//      {{0.0f,  1.0f, 0.0f}, {0.5, 0.0, 0.5, 0.5}},
//
//      {{0.0f, 1.0f, 1.0f}, {0.0, 0.5, 0.25, 0.5}},
//      {{0.0f, 1.0f, -1.0f}, {0.0, 0.5, 0.0, 0.5}},
//      {{0.0f, -1.0f, 0.0f}, {0.75, 0.5, 0.0, 0.5}}
//  };

  static const Vertex vertices[] = {
      {{-1.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0}},
      {{-1.0, 0.0, -1.0}, {0.0, 1.0, 0.0, 1.0}},
      {{0.0, 2.0, 0.0}, {0.0, 0.0, 1.0, 1.0}},

      {{-1.0, 0.0, -1.0}, {0.0, 1.0, 0.0, 1.0}},
      {{1.0, 0.0, -1.0}, {1.0, 0.0, 0.0, 1.0}},
      {{0.0, 2.0, 0.0}, {0.0, 0.0, 1.0, 1.0}},

      {{1.0, 0.0, -1.0}, {1.0, 0.0, 0.0, 1.0}},
      {{1.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}},
      {{0.0, 2.0, 0.0}, {0.0, 0.0, 1.0, 1.0}},

      {{1.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}},
      {{-1.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0}},
      {{0.0, 2.0, 0.0}, {0.0, 0.0, 1.0, 1.0}},

      {{-1.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0}},
      {{0.0, -2.0, 0.0}, {0.0, 0.0, 1.0, 1.0}},
      {{-1.0, 0.0, -1.0}, {0.0, 1.0, 0.0, 1.0}},

      {{-1.0, 0.0, -1.0}, {0.0, 1.0, 0.0, 1.0}},
      {{0.0, -2.0, 0.0}, {0.0, 0.0, 1.0, 1.0}},
      {{1.0, 0.0, -1.0}, {1.0, 0.0, 0.0, 1.0}},

      {{1.0, 0.0, -1.0}, {1.0, 0.0, 0.0, 1.0}},
      {{0.0, -2.0, 0.0}, {0.0, 0.0, 1.0, 1.0}},
      {{1.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}},

      {{1.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}},
      {{0.0, -2.0, 0.0}, {0.0, 0.0, 1.0, 1.0}},
      {{-1.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0}}
  };

  GLuint vertex_buffer_id;
  glGenBuffers(1, &vertex_buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
               vertices, GL_STATIC_DRAW);

  glUseProgram(programID);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);

  glUniformMatrix4fv(projection_id, 1, GL_FALSE, glm::value_ptr(projection));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, position)
  );

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
    1,
    4,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, color)
  );

  auto angle = 0.0f;
  auto dist = 10.0f;
  do {
    angle += 0.04f;
    view = glm::lookAt(glm::vec3(dist * std::cos(angle), 4, dist * std::sin(angle)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(view_id, 1, GL_FALSE, glm::value_ptr(view));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(Vertex));
    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &vertex_buffer_id);
	glDeleteVertexArrays(1, &vertex_array_id);
	glDeleteProgram(programID);

	glfwTerminate();

  return 0;
}