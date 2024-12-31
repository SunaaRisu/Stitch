#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Display {
public:
  Display(int width, int height, const char* title);
  
  void Clear(float r, float g, float b, float a);
  void Update();
  bool IsClosed();

  virtual ~Display();

private:
  GLFWwindow* m_window;
};

#endif // !DISPLAY_H
