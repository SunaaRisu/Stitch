#pragma once
#ifndef VAO_H

#define ASSERT(x) if (!(x)) __builtin_trap();

#include <GL/glew.h>
#include <vector>


// VertexBuffer

class VertexBuffer {
private:
  unsigned int m_RendererID;

public:
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;
};



// VertexBufferLayout

struct VertexBufferElement {
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetSizeOfType(unsigned int type) {
    switch (type) {
      case GL_FLOAT:          return 4;
      case GL_UNSIGNED_INT:   return 4;
      case GL_UNSIGNED_BYTE:  return 1;
    }
    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout {
private:
  std::vector<VertexBufferElement> m_Elements;
  unsigned int m_Stride;

public:
  VertexBufferLayout()
    : m_Stride(0) {}

  template<typename T>
  void Push(unsigned int count) {
    static_assert(false);
  }

  inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
  inline unsigned int GetStride() const { return m_Stride; }
};

template <>
inline void VertexBufferLayout::Push<float>(unsigned int count) {
  m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
  m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template <>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
  m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
  m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template <>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
  m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
  m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}



// VertexArray

class VertexArray {
private:
  unsigned int m_RendererID;

public:
  VertexArray();
  VertexArray(const void* data, unsigned int size, const VertexBufferLayout& layout);
  ~VertexArray();

  void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

  void Bind() const;
  void Unbind() const;
};

#endif // !VAO_H
