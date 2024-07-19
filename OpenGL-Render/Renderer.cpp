#include "Renderer.h"
#include <iostream>

void GLCleanError()
{
    while (glGetError() != GL_NO_ERROR)
    {
        ;
    }
}

bool GLLogCall(const char* function, const char* file, int line)
{
    if (GLenum error = glGetError())
    {
        std::cout << "[" << error << "]," << function
            << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuff& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();

    shader.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr))
}

void Renderer::Clear()const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}