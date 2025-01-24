#include "Camera.h"

Camera::Camera() {}

glm::mat4 Camera::getViewMatrix()
{
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, -this->position);

    return view;
}