#include <assert.h>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "config.h"
#include "shaders.h"
#include "camera.h"
#include "render.h"
#include "stb_image.h"

using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* initWindow();

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float runningTime = 0.0f;

int main() {
    GLFWwindow* window = initWindow();

    Shader shader("../src/shaders/default.vert", "../src/shaders/default.frag");

    Camera camera;

    Renderer renderer;
    renderer.init();

    // Load texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("../textures/brick.png", &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // Bind uniforms
    shader.use();
    shader.setInt("ourTexture", 0);

    mat4 model = mat4(1.0);
    shader.setMat4("model", model);

    mat4 view = mat4(1.0);
    shader.setMat4("view", view);

    mat4 projection;
    projection = ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    int frames = 0;
    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        runningTime += deltaTime;

        if(runningTime >= 1.0f) {
            std::cout << "FPS: " << float(frames) / runningTime << std::endl;
            frames = 0;
            runningTime = 0.0f;
        }


        processInput(window);
        // TODO: Update camera based on player position rather than window events
        camera.processInput(window, deltaTime);

        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        view = camera.getViewMatrix();
        shader.setMat4("view", view);

        renderer.render();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        ++frames;
    }
    
    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* initWindow() {
    assert((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT == ASPECT); 

    glewExperimental = true;
    if(!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
    }  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Super Mario Bros.", NULL, NULL);
    if( window == NULL ){
        std::cout << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW." << std::endl;
    }
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    return window;
}
