#include "utils.h"


std::string loadShader(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("Failed to open shader: " + filepath);

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
