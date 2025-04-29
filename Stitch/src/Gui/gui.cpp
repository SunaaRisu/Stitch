#include "gui.h"

Gui::Gui(GLFWwindow *window, GUI_STYLE style) {
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");
  switch (style) {
    case GUI_STYLE::CLASSIC:
      ImGui::StyleColorsClassic();
      break;

    case GUI_STYLE::DARK:
      ImGui::StyleColorsDark();
      break;

    case GUI_STYLE::LIGHT:
      ImGui::StyleColorsLight();
      break;

    default:
      ImGui::StyleColorsDark();
      break;
  }
}

Gui::~Gui() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void Gui::Clear() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void Gui::Draw() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
