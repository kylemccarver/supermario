#include <GL/glew.h>
#include <OpenGL/gl.h>

#include "config.h"
#include "render.h"

using namespace glm;

void Renderer::init() {
    glGenVertexArrays(1, &VAObg);
    glGenBuffers(1, &VBObg);

    glBindVertexArray(VAObg);

    generateBackgroundQuads(bgVertices, texCoords);

    glBindBuffer(GL_ARRAY_BUFFER, VBObg);
    glBufferData(GL_ARRAY_BUFFER, bgVertices.size() * sizeof(vec4), &bgVertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::render() {
    renderBackground();
}

void Renderer::renderBackground() {
    glBindVertexArray(VAObg);
    glDrawArrays(GL_TRIANGLES, 0, bgVertices.size());
    glBindVertexArray(0);
}


void Renderer::generateBackgroundQuads(std::vector<glm::vec4>& vertices, std::vector<glm::vec2>& texCoords) {
    for(int y = 0; y < TILES_Y; ++y) {
        for(int x = 0; x < TILES_X; ++x) {
            float y1 = y * TILE_SIZE;
            float x1 = x * TILE_SIZE;
            float y2 = (y + 1) * TILE_SIZE;
            float x2 = (x + 1) * TILE_SIZE;

            // First triangle
            vertices.push_back(vec4(x1, y1, 0.0, 1.0)); // Top left 
            texCoords.push_back(vec2(0.0, 1.0)); // Top left
            vertices.push_back(vec4(x1, y2, 0.0, 1.0)); // Bottom left
            texCoords.push_back(vec2(0.0, 0.0)); // Bottom left
            vertices.push_back(vec4(x2, y1, 0.0, 1.0)); // Top right 
            texCoords.push_back(vec2(1.0, 1.0)); // Top right
            // Second triangle
            vertices.push_back(vec4(x2, y2, 0.0, 1.0)); // Bottom right 
            texCoords.push_back(vec2(1.0, 0.0)); // Bottom right
            vertices.push_back(vec4(x2, y1, 0.0, 1.0)); // Top right
            texCoords.push_back(vec2(1.0, 1.0)); // Top right
            vertices.push_back(vec4(x1, y2, 0.0, 1.0)); // Bottom left
            texCoords.push_back(vec2(0.0, 0.0)); // Bottom left
        }
    }
}

