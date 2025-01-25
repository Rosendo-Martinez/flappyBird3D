#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "SquareRender.h"
#include "Camera.h"
#include "FlappyBird.h"
#include "LineRender.h"

#include <glm/mat4x4.hpp> 
#include <glm/ext/matrix_clip_space.hpp> 
#include <glm/gtc/type_ptr.hpp>

const unsigned int SCREEN_WIDTH = 1600;
const unsigned int SCREEN_HEIGHT = 900;

Camera cam;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;

float lastFrame = 0.0f;
float dt = 0.0f;

FlappyBird bird;
bool flap = false;

void processInput(GLFWwindow* window);

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

    // Square rendering init
    Shader squareShader;
    squareShader.compile("./shaders/square.vs", "./shaders/square.fs");
    SquareRender squareRender(squareShader);

    // Line rendering init
    Shader lineShader;
    lineShader.compile("./shaders/line.vs", "./shaders/line.fs");
    LineRender lineRender(lineShader);

    cam.position = glm::vec3(0.0f, 0.0f, 25.f);
    bird.position = glm::vec3(0.0, 0.0f, 0.0f);
    bird.velocity = glm::vec3(0.0, 5.0f, 0.0f);

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        bird.move(dt, flap);
        cam.setFacingDir(pitch, yaw);

        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 250.0f);
        glm::mat4 view = cam.getViewMatrix();

        // set projection and view matrix
        lineShader.use();
        glUniformMatrix4fv(glGetUniformLocation(lineShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lineShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        squareShader.use();
        glUniformMatrix4fv(glGetUniformLocation(squareShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(squareShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // draw squares
        squareRender.draw(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-5.0f, -0.f, 0.f));
        squareRender.draw(glm::vec3(1.0f, 0.0f, 0.1f), glm::vec3(3.f, 5.f, 0.f));
        squareRender.draw(glm::vec3(1.0f, 0.0f, 0.3f), bird.position);

        // draw coordinate axes
        lineRender.draw(glm::vec3(0.0f), glm::vec3(1.0,0.0,0.0), glm::vec3(1.0,0.0,0.0)); // x-axis
        lineRender.draw(glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0), glm::vec3(0.01,0.01,0.01)); // y-axis
        lineRender.draw(glm::vec3(0.0f), glm::vec3(0.0,0.0,1.0), glm::vec3(1.0,1.0,1.0)); // z-axis
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    // camera movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cam.position += cam.facingDir * 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cam.position -= cam.facingDir * 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cam.position -= glm::normalize(glm::cross(cam.facingDir, cam.up)) * 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cam.position += glm::normalize(glm::cross(cam.facingDir, cam.up)) * 0.1f;
    }

    // camera facing direction
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        pitch += 0.2f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        pitch -= 0.2f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        yaw -= 0.2f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        yaw += 0.2f;
    }
    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    // camera fov
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        fov -= 0.5f;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        fov += 0.5f;
    }

    if (fov < 10.f)
    {
        fov = 10.f;
    }
    else if (fov > 90.f)
    {
        fov = 90.0f;
    }

    // bird flap
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        flap = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        flap = false;
    }
}