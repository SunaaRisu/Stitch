#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp> // This is just for the SetUniformMat4f Function. Maybe remove later.

struct ShaderProgramSource {
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader {
private:
  std::string m_SrcFilePath;
  unsigned int m_ProgramID;
  std::unordered_map<std::string, int> m_UniformLocationCache;

public:
  Shader(const std::string &filePath);
  ~Shader();

  void Bind() const;
  void Unbind() const;
  void Update() const;

  // Set uniforms
  void SetUniform1i(const std::string& name, int value);
  void SetUniform1f(const std::string& name, float value);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
  ShaderProgramSource ParseShader(const std::string& filePath);
  unsigned int CompileShader(unsigned int type, const std::string& source);
  unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
  bool CheckError(unsigned int program, unsigned int flag, bool isProgram, const std::string &errorMessage);
  int GetUniformLocation(const std::string& name);
};

#endif // !SHADER_H
