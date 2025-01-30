#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp> 
#include <glm/ext/matrix_clip_space.hpp> 
#include <glm/ext/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

#include <glad/glad.h>

class CubeRender
{
private:
    unsigned int VAO;
    Shader shader;

public:
    CubeRender(Shader shader);

    void draw(glm::vec4 color, glm::mat4 model);
    glm::mat4 getModelMatrix(glm::vec3 pos, glm::vec3 size);
};