#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "IndexBuff.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLCleanError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLCleanError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:

    void Clear() const;
	void Draw(const VertexArray& va, const IndexBuff& ib, const Shader& shader) const;

private:

};
