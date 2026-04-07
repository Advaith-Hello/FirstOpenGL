#pragma once

#include <string>


std::string loadShader(const std::string& filepath);
void checkShaderError(GLuint shader, GLenum type);
