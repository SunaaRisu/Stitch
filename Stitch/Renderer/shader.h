#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

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
