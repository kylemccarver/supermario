#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

using namespace glm;

// TODO: initializer list/signature thingy
Camera::Camera() {
    pos = vec3(0.0, 0.0, 1.0);
    up = vec3(0.0, 1.0, 0.0);
    right = vec3(1.0, 0.0, 0.0);
    direction = vec3(0.0, 0.0, -1.0);
}

mat4 Camera::getViewMatrix() {
    return lookAt(pos, pos + direction, up);
}

void Camera::processInput(GLFWwindow* window, float deltaTime) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += direction * speed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos-= direction * speed * deltaTime;;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= right * speed * deltaTime;;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += right * speed * deltaTime;;
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        pos += up * speed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        pos -= up * speed * deltaTime;
}
