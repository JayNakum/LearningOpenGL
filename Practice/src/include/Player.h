#include "engine/Renderer.h"

#include "../vendors/glm/glm.hpp"

#include "engine/Texture.h"
#include "engine/Shader.h"

class Player
{
public:
    float yVelocity;
    glm::vec3 translation;

public:
    Player(Shader *shader);
    ~Player();

public:
    void render(Renderer &renderer);

private:
    const float *m_Position;
    const unsigned int *m_Indices;
    Shader *m_shader;
    Texture *m_texture;
    VertexArray *va;
    VertexBuffer *vb;
    VertexBufferLayout *layout;
    IndexBuffer *ib;
};
