#pragma once
#include "VertexBuff.h"

class VertexBuffLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void UnBind() const;
	void AddBuff(const VertexBuff& vb, const VertexBuffLayout& layout) const;
};