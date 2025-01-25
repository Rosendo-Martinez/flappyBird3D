#include "LineRender.h"

LineRender::LineRender(Shader shader) 
{
    // line
    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
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

void LineRender::draw(glm::vec3 start, glm::vec3 end, glm::vec3 color) 
{
    this->shader.use();

    glUniform3fv(glGetUniformLocation(this->shader.ID, "start"), 1, &start[0]);
    glUniform3fv(glGetUniformLocation(this->shader.ID, "end"), 1, &end[0]);
    glUniform3fv(glGetUniformLocation(this->shader.ID, "color"), 1, &color[0]);

    // draw lines
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_LINES, 0, 2);

    // unbind
    glBindVertexArray(0);
    glUseProgram(0);
}