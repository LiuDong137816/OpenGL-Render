#pragma once
#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexArray.h"
#include "Texture.h"

#include <memory>

namespace test
{
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime)override;
		void OnRender()override;
		void OnImGuiRender()override;

	private:
		glm::vec3 m_TranslationA, m_TranslationB;
		glm::mat4 m_Proj, m_View;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuff> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::vector<std::unique_ptr<Texture>> m_Textures;
		std::unique_ptr<VertexBuff> m_VertexBuffer;
	};

	
}