#include "vao.h"

// VertexBuffer

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
  glGenBuffers(1, &m_RendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}



// VertexArray

VertexArray::VertexArray() {
  glGenVertexArrays(1, &m_RendererID);
}

VertexArray::VertexArray(const void* data, unsigned int size, const VertexBufferLayout& layout) {
  glGenVertexArrays(1, &m_RendererID);
  VertexBuffer vb(data, size);
  Bind();
  vb.Bind();
  const auto& elements = layout.GetElements();
  unsigned long offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++) {
    const auto& element = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type,
                          element.normalized, layout.GetStride(),
                          (const void*)offset);
    offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
  }
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
  Bind();
  vb.Bind();
  const auto& elements = layout.GetElements();
  unsigned long offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++) {
    const auto& element = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type,
                          element.normalized, layout.GetStride(),
                          (const void*)offset);
    offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
  }
}

void VertexArray::Bind() const {
  glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
  glBindVertexArray(0);
}
