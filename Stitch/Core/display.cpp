#include "display.h"
#include <iostream>

Display::Display(int width, int height, const char* title) {
  if (!glfwInit())
    std::cerr << "GLFW failed to initialize!" << std::endl;

  m_window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!m_window) {
    glfwTerminate();
    std::cerr << "Window failed to be created!" << std::endl;
  }

  glfwMakeContextCurrent(m_window);

  if (glfwInit() != GLEW_OK) {
    std::cerr << "GLEW failed to initialize!" << std::endl;
  }

  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

Display::~Display() {
  glfwTerminate();
}

void Display::Clear(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT);
}

bool Display::IsClosed() {
  return glfwWindowShouldClose(m_window);
}

void Display::Update() {  
  glfwSwapBuffers(m_window);

  glfwPollEvents();
}
