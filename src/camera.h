#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
    public:
        Camera();
        glm::mat4 look();
    private:
        glm::vec3 pos;
        glm::vec3 up;
        glm::vec3 direction;
        glm::vec3 right;
};
#endif
