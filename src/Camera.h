#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp> 
#include <glm/ext/matrix_transform.hpp> 

/**
 * It handles all operations on camera:
 *   move
 *   rotate/point its direction
 *   even change fov, maybe even near and far
 * 
 * All features will be good for debuging.
 */
class Camera
{
public:
    glm::vec3 position; // position of camera

    Camera();
    glm::mat4 getViewMatrix();
};