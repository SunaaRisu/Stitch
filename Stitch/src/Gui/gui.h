#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"

enum class GUI_STYLE {CLASSIC, DARK, LIGHT};

class Gui {
public:
  Gui(GLFWwindow *window, GUI_STYLE style);
  ~Gui();

  void Clear();
  void Draw();
};
