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
  m_vbRendererID = 0;
  glGenVertexArrays(1, &m_RendererID);
}

VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout) {
  m_vbRendererID = 0;
  glGenVertexArrays(1, &m_RendererID);
  AddBuffer(vb, layout);
}

VertexArray::VertexArray(const void* data, unsigned int size, const VertexBufferLayout& layout) {
  glGenBuffers(1, &m_vbRendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbRendererID);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

  glGenVertexArrays(1, &m_RendererID);
  Bind();
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
  if (m_vbRendererID) {
    glDeleteBuffers(1, &m_vbRendererID);
  }
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
