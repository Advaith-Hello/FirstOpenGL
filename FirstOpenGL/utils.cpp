#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "utils.h"


std::string loadShader(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("Failed to open shader: " + filepath);

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void checkShaderError(GLuint shader, GLenum type) {
    GLint success;
    GLchar log[1024];

    if (type == GL_COMPILE_STATUS) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, sizeof(log), NULL, log);
            std::cerr << "Shader compile error: " << log << "\n";
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, sizeof(log), NULL, log);
            std::cerr << "Program link error: " << log << "\n";
        }
    }
}
