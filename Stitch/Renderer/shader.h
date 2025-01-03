#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
public:
  Shader(const std::string &filePath);

  void Bind();
  void Update();

  ~Shader();

private:
  unsigned int m_program;
};

#endif // !SHADER_H
