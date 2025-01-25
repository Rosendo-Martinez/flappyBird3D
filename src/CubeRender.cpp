#include "CubeRender.h"

CubeRender::CubeRender(Shader shader)
{
    const float vertices[] = 
    {
        // Front face
        // A, C, B
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        // D, B, C
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        // Back face
        // E, F, G
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        // H, G, F
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,

        // Top face
        // E, A, F
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        // B, F, A
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,

        // Left face
        // A, E, C
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        // G, C, E
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,

        // Right face
        // B, D, F
        0.5f,  0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        // H, F, D
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,

        // Bottom face
        // G, H, C
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        // D, C, H
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f
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

void CubeRender::draw(glm::vec3 color, glm::mat4 model)
{
    this->shader.use();

    // set model matrix
    glUniformMatrix4fv(glGetUniformLocation(this->shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));    

    // set color
    glUniform3fv(glGetUniformLocation(this->shader.ID, "color"), 1, &color[0]);

    // Draw cube
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // unbind
    glBindVertexArray(0);
    glUseProgram(0);
}

glm::mat4 CubeRender::getModelMatrix(glm::vec3 pos, glm::vec3 size)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, size);

    return model;
}