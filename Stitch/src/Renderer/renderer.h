#ifndef RENDERER_H
#define RENDERER_H

#include "ib.h"
#include "vao.h"
#include "shader.h"

class Renderer {
public:
  void Clear() const;
  void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

#endif // !RENDERER_H
