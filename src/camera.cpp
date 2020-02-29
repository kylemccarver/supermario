#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

using namespace glm;

// TODO: initializer list/signature thingy
Camera::Camera() {
}

mat4 Camera::look() {
    return lookAt(pos, direction, up);
}
