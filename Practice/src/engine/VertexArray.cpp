#include "../include/engine/VertexArray.h"

#include "../include/engine/GLErrorManager.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    bind();
    vb.bind();
    const auto &elements = layout.getElements();
    intptr_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *) offset)); // position layout
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const
{ 
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}