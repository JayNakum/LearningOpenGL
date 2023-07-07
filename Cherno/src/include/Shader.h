#pragma once

#include <string>
#include <unordered_map>

#include "../vendors/glm/glm.hpp"

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    // caching for uniforms
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string &filePath);
    ~Shader();

public:
    void bind() const;
    void unbind() const;
    void setUniform1i(const std::string &name, int value);
    void setUniform1f(const std::string &name, float value);
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);

private:
    int getUniformLocation(const std::string &name);

    ShaderProgramSource parseShader(const std::string &filePath);
    unsigned int compileShader(unsigned int type, const std::string &source);
    unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);
};