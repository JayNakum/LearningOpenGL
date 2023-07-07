#include "include/Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "include/GLErrorManager.h"

Shader::Shader(const std::string &filePath)
    : m_FilePath(filePath), m_RendererID(0)
{
    ShaderProgramSource source = parseShader(filePath);
    // std::cout << "Vertex Shader:" << std::endl;
    // std::cout << source.vertexSource << std::endl;
    // std::cout << "Fragment Shader:" << std::endl;
    // std::cout << source.fragmentSource << std::endl;
    m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string &name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}
void Shader::setUniform1f(const std::string &name, float value)
{
    GLCall(glUniform1f(getUniformLocation(name), value));
}
void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}
void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "[WARNING] uniform " << name << " doesn't exist." << std::endl;
    m_UniformLocationCache[name] = location;
    return location;
}

ShaderProgramSource Shader::parseShader(const std::string &filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType mode = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                mode = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                mode = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)mode] << line << "\n";
        }
    }

    return {ss[0].str(), ss[1].str()};
}
unsigned int Shader::compileShader(unsigned int type, const std::string &source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str(); // &source[0]
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); // i <-- Integer v <-- Vector / array / pointer

    if (result == GL_FALSE) // GL_FALSE = 0
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "[Vertex" : "[Fragment")
                  << " Shader]" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}
unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}