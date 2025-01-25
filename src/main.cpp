#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "SquareRender.h"
#include "Camera.h"
#include "FlappyBird.h"

#include <glm/mat4x4.hpp> 
#include <glm/ext/matrix_clip_space.hpp> 
#include <glm/gtc/type_ptr.hpp>

const unsigned int SCREEN_WIDTH = 1600;
const unsigned int SCREEN_HEIGHT = 900;

FlappyBird bird;

Camera cam;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;

float lastFrame = 0.0f;
float dt = 0.0f;

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

    // set up for rendering square
    Shader testShader;
    testShader.compile("./shaders/square.vs", "./shaders/square.fs");
    SquareRender testRender(testShader);
    testShader.use();

    cam.position = glm::vec3(0.0f, 0.0f, 25.f);

    bird.position = glm::vec3(0.0, 0.0f, 0.0f);
    bird.velocity = glm::vec3(0.0, 5.0f, 0.0f);

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        bird.move(dt, flap);

        processInput(window);

        cam.setFacingDir(pitch, yaw);

        testShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 250.0f);
        glUniformMatrix4fv(glGetUniformLocation(testShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glm::mat4 view = cam.getViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(testShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw here
        testRender.draw(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-5.0f, -0.f, 0.f));
        testRender.draw(glm::vec3(1.0f, 0.0f, 0.1f), glm::vec3(3.f, 5.f, 0.f));
        testRender.draw(glm::vec3(1.0f, 0.0f, 0.3f), bird.position);
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
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

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        flap = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        flap = false;
    }
}