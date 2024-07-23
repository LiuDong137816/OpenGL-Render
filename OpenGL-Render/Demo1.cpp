#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Renderer.h"
#include "VertexBuffLayout.h"
#include "IndexBuff.h"
#include "VertexBuff.h"
#include "VertexArray.h"

#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"
#include "Vendor/imgui/imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* glsl_version = "#version 130";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    //Shader shader("C:\\Users\\liu18\\source\\repos\\OpenGL-Render\\OpenGL-Render\\OpenGL.Shader");
    std::string projectPath = std::filesystem::current_path().string();
    Shader shader(projectPath + "/Res/Shaders/OpenGL.Shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.7f, 0.5f, 1.0f);

    Texture texture(projectPath + "/Vendor/stb_image/Retangle.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    

   
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
    {
        float vertices[] = {
            // first triangle
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // left 
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // right
             0.5f, 0.5f, 0.0f,  1.0f, 1.0f, // top 
             -0.5f, 0.5f, 0.0f, 0.0f, 1.0f// top 
        };

        unsigned int indices[]
        {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuff vbo(vertices, 4 * 5 * sizeof(float));
        VertexBuffLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuff(vbo, layout);

        //GLCall(glEnableVertexAttribArray(0));
        //GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));


        IndexBuff ib(indices, 6);
        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0));

        glm::mat4 mvp = proj * view * model;

        shader.SetUniformMat4f("u_MVP", mvp);
        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the    vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        
        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify   this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind   VAOs (nor VBOs) when it's not directly necessary.
        //GLCall(glBindVertexArray(0));
        va.UnBind();
        vbo.UnBind();
        ib.UnBind();
        shader.UnBind();

        Renderer renderer;

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            processInput(window);

            // render
            // ------
            //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            shader.Bind();

            double  timeValue = glfwGetTime();
            float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
            shader.SetUniform4f("u_Color", 0.8f, greenValue, 0.5f, 1.0f);
            // draw our first triangle

            //GLCall(glBindVertexArray(VAO)); // seeing as we only have a single VAO there's no    need to bind it every time, but we'll do so to keep things a bit more     organized
            
            renderer.Draw(va, ib, shader);

            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved    etc.)
                //  -------------------------------------------------------------------------------
            GLCall(glfwSwapBuffers(window));
            GLCall(glfwPollEvents());
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        //glDeleteVertexArrays(1, &VAO);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}