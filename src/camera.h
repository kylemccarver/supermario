#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
    public:
        Camera();
        glm::mat4 getViewMatrix();
        void processInput(GLFWwindow* window, float deltaTime);
    private:
        glm::vec3 pos;
        glm::vec3 up;
        glm::vec3 direction;
        glm::vec3 right;
        const float speed = 16.0f;
};
#endif
