#include <filesystem>

#include "TestTexture2D.h"

#include "Renderer.h"
#include "Vendor/imgui/imgui.h"
#include "VertexBuff.h"
#include "VertexBuffLayout.h"

#include "Texture.h"

namespace test
{
	TestTexture2D::TestTexture2D()
        : m_TranslationA(0, 0, 0), m_TranslationB(2.5, 2.5, 0)
	{
        std::string projectPath = std::filesystem::current_path().string();
        m_Shader = std::make_unique<Shader>(projectPath + "/Res/Shaders/OpenGL.Shader");
        m_VAO = std::make_unique<VertexArray>();

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 0.8f, 0.7f, 0.5f, 1.0f);


        float vertices[] = {
            // first triangle
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // left 
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // right
             0.5f, 0.5f, 0.0f,  1.0f, 1.0f, // top 
             -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,// top 

              1.5f, 1.5f, 0.0f, 0.0f, 0.0f,  // left 
             2.5f, 1.5f, 0.0f,  1.0f, 0.0f, // right
             2.5f, 2.5f, 0.0f,  1.0f, 1.0f, // top 
             1.5f, 2.5f, 0.0f, 0.0f, 1.0f// top 
        };

        unsigned int indices[]
        {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VertexBuffer = std::make_unique<VertexBuff>(vertices, 8 * 5 * sizeof(float));
        VertexBuffLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VAO->AddBuff(*m_VertexBuffer, layout);

        m_Proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);
        m_View = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0, 0));

        m_Shader->Bind();
        m_IndexBuffer = std::make_unique<IndexBuff>(indices, 12);
        m_Texture = std::make_unique<Texture>(projectPath + "/Vendor/stb_image/Retangle.png");
        m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;

            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        /*{
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;

            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }*/
	}

	void TestTexture2D::OnImGuiRender()
	{
        ImGui::SliderFloat3("tranlation_A", &m_TranslationA.x, 0.0f, 1.0f);
        //ImGui::SliderFloat3("tranlation_B", &m_TranslationB.x, 0.0f, 1.0f);
        
	}
}
