#ifndef IB_H
#define IB_H

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __builtin_trap();

class IndexBuffer {
private:
  unsigned int m_RendererID;
  unsigned int m_Count;

public:
  IndexBuffer(const unsigned int* data, unsigned int count);
  ~IndexBuffer();

  void Bind() const;
  void Unbind() const;

  inline unsigned int GetCount() const { return m_Count; }
};

#endif // !IB_H
