#include "include/Player.h"

#include "include/engine/Screen.h"

#include <iostream>

extern struct ScreenSize screenSize;

Player::Player(Shader *shader)
    : translation(0.0f, 0.0f, 0.0f), m_shader(shader),
      m_texture(new Texture("../res/textures/plane2.png"))
{
    m_Position = new float[16]{
        -40.0f, -40.0f, 0.0f, 0.0f,
        40.0f, -40.0f, 1.0f, 0.0f,
        40.0f, 40.0f, 1.0f, 1.0f,
        -40.0f, 40.0f, 0.0f, 1.0f};

    m_Indices = new unsigned int[6]{
        0, 1, 2,
        2, 3, 0};

    yVelocity = -7.0f;

    m_texture->bind();
    m_shader->bind();
    m_shader->setUniform1i("u_Texture", 0);

    va = new VertexArray();
    vb = new VertexBuffer(m_Position, 4 * 4 * sizeof(float));
    layout = new VertexBufferLayout();
    layout->push<float>(2);
    layout->push<float>(2);
    va->addBuffer(*vb, *layout);
    ib = new IndexBuffer(m_Indices, 6);
}

void Player::render(Renderer &renderer)
{
    renderer.draw(*va, *ib, *m_shader);
    if (translation.y - 40 > screenSize.bottomEdge())
    {
        translation.y += yVelocity;
    }
}

Player::~Player()
{
    delete[] m_Position;
    delete[] m_Indices;
    delete m_texture;
    delete va;
    delete vb;
    delete layout;
    delete ib;
}
