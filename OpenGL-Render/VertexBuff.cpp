#include"VertexBuff.h"

#include "Renderer.h"

VertexBuff::VertexBuff(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuff::~VertexBuff()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuff::Bind() const
{
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuff::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}