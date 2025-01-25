#include "Shader.h"
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/type_ptr.hpp>

class LineRender
{
private:
    unsigned int VAO;
    Shader shader;
public:
    LineRender(Shader shader);
    void draw(glm::vec3 start, glm::vec3 end, glm::vec3 color);
};