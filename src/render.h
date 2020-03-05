#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <glm/glm.hpp>

class Renderer {
    public:
        void init();
        void render();
    private:
        unsigned int VAObg;
        unsigned int VBObg;

        std::vector<glm::vec4> bgVertices;
        std::vector<glm::vec2> texCoords;

        void renderBackground();
        void generateBackgroundQuads(std::vector<glm::vec4>& vertices, std::vector<glm::vec2>& texCoords);
};

#endif
