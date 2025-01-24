#include "Camera.h"
#include <cmath>

Camera::Camera() {}

void Camera::setFacingDir(float pitch, float yaw)
{
    // not 100% on this math, I'd say 50% but eh
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    this->facingDir = glm::normalize(direction);
}

glm::mat4 Camera::getViewMatrix()
{
    // glm::mat4 view = glm::mat4(1.0f);
    // view = glm::translate(view, -this->position);

    // glm::vec3 center = 


    glm::mat4 view = glm::lookAt(this->position, this->position + this->facingDir, glm::vec3(0.0f,1.0f,0.0f));
    return view;
}