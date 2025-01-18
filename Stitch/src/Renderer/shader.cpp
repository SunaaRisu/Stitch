#include "shader.h"

#include <alloca.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Shader::Shader(const std::string &filePath)
    : m_SrcFilePath(filePath), m_ProgramID(0) {
  ShaderProgramSource source = ParseShader(filePath);
  m_ProgramID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() { glDeleteProgram(m_ProgramID); }

ShaderProgramSource Shader::ParseShader(const std::string &filePath) {
  std::ifstream stream(filePath);

  enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;
  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    } else {
      ss[(int)type] << line << '\n';
    }
  }

  return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type,
                                  const std::string &source) {
  unsigned int id = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  if (CheckError(id, GL_COMPILE_STATUS, false,
                 "Error: Shader compilation failed: "))
    return 0;

  return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader,
                                 const std::string &fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  if (CheckError(program, GL_LINK_STATUS, true,
                 "Error: Program linking failed: "))
    return 0;
  glValidateProgram(program);
  if (CheckError(program, GL_VALIDATE_STATUS, true,
                 "Error: Program is invalid: "))
    return 0;
  ;

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

bool Shader::CheckError(unsigned int program, unsigned int flag, bool isProgram,
                       const std::string &errorMessage) {
  int success = 0;

  if (isProgram)
    glGetProgramiv(program, flag, &success);
  else
    glGetShaderiv(program, flag, &success);

  if (!success) {
    if (isProgram) {
      int length;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
      char *message = (char *)alloca(length * sizeof(char));
      glGetProgramInfoLog(program, length, &length, message);
      std::cerr << errorMessage << ": '" << message << "'" << std::endl;
      glDeleteProgram(program);
    } else {
      int length;
      glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
      char *message = (char *)alloca(length * sizeof(char));
      glGetShaderInfoLog(program, length, &length, message);
      std::cerr << errorMessage << ": '" << message << "'" << std::endl;
      glDeleteShader(program);
    }
    return true;
  }
  return false;
}

void Shader::Bind() const { glUseProgram(m_ProgramID); }

void Shader::Unbind() const { glUseProgram(0); }

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
  glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

int Shader::GetUniformLocation(const std::string& name) {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
    return m_UniformLocationCache[name];
  }

  int location = glGetUniformLocation(m_ProgramID, name.c_str());
  if (location == -1) {
    std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
  }
  m_UniformLocationCache[name] = location;
  return location;
}
