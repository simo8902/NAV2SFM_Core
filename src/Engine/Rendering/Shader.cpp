//
// Created by Simeon-PC on 3/28/2024.
//

#include "glad/glad.h"
#include <fstream>
#include "Shader.h"
#include "gtc/type_ptr.hpp"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    : vertexShaderFilename(vertexPath), fragmentShaderFilename(fragmentPath) {

    // Read shader code from file paths
    std::string vertexCode = readFile(vertexPath.c_str());    // Correct path variable
    std::string fragmentCode = readFile(fragmentPath.c_str()); // Correct path variable

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);

    checkCompileStatus(vertexShader, "VERTEX");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);

    checkCompileStatus(fragmentShader, "FRAGMENT");

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &matrix) const {
    GLuint uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
    if (uniformLocation == -1) {
        std::cerr << "Uniform '" << name << "' not found in shader (Program ID: "
                    << shaderProgram << ")." << std::endl;
        std::cerr << "Vertex Shader: " << vertexShaderFilename << std::endl;
        std::cerr << "Fragment Shader: " << fragmentShaderFilename << std::endl;

        return;
    }
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

std::string Shader::readFile(const char *filePath) {
    std::ifstream shaderFile(filePath);
    return std::string((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
}

void Shader::checkCompileStatus(unsigned int shader, const std::string &type) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader compilation failed for type: " << type << "\n" << infoLog << std::endl;
    }
}


void Shader::Use() const {
    glUseProgram(shaderProgram);
}

