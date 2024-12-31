#include "Stitch/Core/display.h"

#define WIDTH 1080
#define HEIGHT 1080

int main() {
  Display display(WIDTH, HEIGHT, "Hello Stitch!");
  
  float positions[6] = {
    -0.5f, -0.5f,
     0.0f,  0.5f,
     0.5f, -0.5f
  };

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  while (!display.IsClosed()) {
    display.Clear(0.1f, 0.1f, 0.1f, 1.0f);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    display.Update();
  }

  return 0;
}
