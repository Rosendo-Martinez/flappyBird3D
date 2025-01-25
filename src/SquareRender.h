#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp> 
#include <glm/ext/matrix_clip_space.hpp> 
#include <glm/ext/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class SquareRender
{
private:
    unsigned int VAO;
    Shader shader;

public:
    SquareRender(Shader shader);

    void draw(glm::vec3 color, glm::mat4 model);
    glm::mat4 getModelMatrix(glm::vec3 pos, glm::vec3 size, float yaw, float pitch);
};