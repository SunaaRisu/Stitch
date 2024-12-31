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
  glBegin(GL_TRIANGLES);
  glVertex2f(-0.5f, -0.5f);
  glVertex2f( 0.0f,  0.5f);
  glVertex2f( 0.5f, -0.5f);
  glEnd();
  
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}
