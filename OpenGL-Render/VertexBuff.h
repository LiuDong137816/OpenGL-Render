#pragma once

class VertexBuff
{
private:
	unsigned int m_RendererID;

public:
	VertexBuff(const void* data, unsigned int size);
	~VertexBuff();

	void Bind() const;
	void UnBind() const;
};