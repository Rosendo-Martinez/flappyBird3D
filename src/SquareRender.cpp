#include "SquareRender.h"

#include <glad/glad.h>


SquareRender::SquareRender(Shader shader)
{
    // square
    float vertices[] = {
        -0.5f,  0.5f, 0.0f, // triangle 1
        -0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,

         0.5f, -0.5f, 0.0f, // triangle 2
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); // bind vao
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    this->VAO = VAO;
    this->shader = shader;
}

/**
 * Draws the square.
 * 
 * Assumes some shader program is being used.
 */
void SquareRender::draw(glm::vec3 color, glm::vec3 pos)
{
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    // model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(this->shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));    

    // set color
    glUniform3fv(glGetUniformLocation(this->shader.ID, "color"), 1, &color[0]);

    // Draw square
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // unbind
    glBindVertexArray(0);
    glUseProgram(0);
}
