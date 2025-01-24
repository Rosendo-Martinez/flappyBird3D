#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "SquareRender.h"
#include "Camera.h"

#include <glm/mat4x4.hpp> 
#include <glm/ext/matrix_clip_space.hpp> 
#include <glm/gtc/type_ptr.hpp>

const unsigned int SCREEN_WIDTH = 1600;
const unsigned int SCREEN_HEIGHT = 900;

int main()
{
    // configure glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird 3D", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set up for rendering square
    Shader testShader;
    testShader.compile("./shaders/square.vs", "./shaders/square.fs");
    SquareRender testRender(testShader);
    Camera cam;
    cam.position = glm::vec3(0.0f, 0.0f, 10.f);

    testShader.use();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 250.0f);
    glUniformMatrix4fv(glGetUniformLocation(testShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 view = cam.getViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(testShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw here
        testRender.draw(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-5.0f, -0.f, -5.f));
        testRender.draw(glm::vec3(1.0f, 0.0f, 0.1f), glm::vec3(0.f, 5.f, -5.f));
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
