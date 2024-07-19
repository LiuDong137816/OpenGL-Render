#pragma once

class IndexBuff
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuff(const unsigned int* data, unsigned int count);
	~IndexBuff();

	void Bind() const;
	void UnBind() const; 

	inline unsigned int GetCount() const
	{
		return m_Count;
	}
};