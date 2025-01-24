#include "Camera.h"
#include <cmath>

Camera::Camera() {}

glm::mat4 Camera::getViewMatrix()
{
    // glm::mat4 view = glm::mat4(1.0f);
    // view = glm::translate(view, -this->position);

    glm::mat4 view = glm::lookAt(this->position, this->position + this->facingDir, glm::vec3(0.0f,1.0f,0.0f));
    return view;
}