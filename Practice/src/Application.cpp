#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "include/engine/Screen.h"
#include "include/engine/GLErrorManager.h"
#include "include/engine/Renderer.h"
#include "include/engine/VertexBuffer.h"
#include "include/engine/IndexBuffer.h"
#include "include/engine/VertexArray.h"
#include "include/engine/Shader.h"
#include "include/engine/Texture.h"

#include "vendors/glm/glm.hpp"
#include "vendors/glm/gtc/matrix_transform.hpp"
#include "vendors/imgui/imgui.h"
#include "vendors/imgui/imgui_impl_glfw.h"
#include "vendors/imgui/imgui_impl_opengl3.h"

#include "include/Player.h"

#define DEBUG true

ScreenSize screenSize;

static bool initGLFW()
{
    /* Initialize the library */
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    screenSize.width = mode->width;
    screenSize.height = mode->height;

    return true;
}

int main(void)
{

    if (!initGLFW())
        return -1;

    GLFWwindow *window;
    window = glfwCreateWindow(screenSize.width, screenSize.height, "Flappy", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    {
        glm::mat4 proj = glm::ortho(
            screenSize.leftEdge(),
            screenSize.rightEdge(),
            screenSize.bottomEdge(),
            screenSize.topEdge(),
            -1.0f, 1.0f);

        Shader shader("../res/shaders/basic.shader");
        shader.bind();
        
        Player plane(&shader);

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), plane.translation);
                glm::mat4 mvp = proj * model;
                shader.bind();
                shader.setUniformMat4f("u_MVP", mvp);
                plane.render(renderer);
            }

            if(DEBUG)
            {
                ImGui::Begin("Debug Menu");

                ImGui::SliderFloat3("Player Position", &plane.translation.x,
                                    screenSize.leftEdge(), screenSize.rightEdge());
                ImGui::SliderFloat("Player Velocity", &plane.yVelocity,
                                    screenSize.topEdge(), screenSize.bottomEdge());
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                            1000.0f / ImGui::GetIO().Framerate,
                            ImGui::GetIO().Framerate);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
