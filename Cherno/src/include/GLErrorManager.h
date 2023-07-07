#pragma once

#include <GL/glew.h>
#include <signal.h>

#define ASSERT(x) \
    if (!(x))     \
        raise(SIGTRAP);

#define GLCall(x)    \
    GLClearErrors(); \
    x;               \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearErrors();

bool GLLogCall(const char *function, const char *file, int line);