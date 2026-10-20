#pragma once

#include "glad/glad.h"

class shader {
public:

    shader() = default;
    ~shader();

    shader(const shader&) = delete;
    shader& operator=(const shader&) = delete;

    shader(shader&& other) noexcept;
    shader& operator=(shader&& other) noexcept;

    bool loadFromFile(const char* vertexPath, const char* fragmentPath);
    bool loadFromText(const char* vertexCode, const char* fragmentCode);

    bool use() const;

private:

    GLuint m_id = 0;

};
