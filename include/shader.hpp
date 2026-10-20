#pragma once

#include "glad/glad.h"

class shader {
public:

    shader() = default;
    ~shader();

    shader(const shader&) = delete;
    shader& operator=(const shader&) = delete;

    shader(shader&& other) noexcept {
        m_id = other.m_id;
        other.m_id = 0;
    }
    shader& operator=(shader&& other) {
        if (this != &other) {
            if (m_id)
                glDeleteProgram(m_id);
            m_id = other.m_id;
            other.m_id = 0;
        }
        return *this;
    }

    bool loadFromFile(const char* vertexPath, const char* fragmentPath);
    bool loadFromText(const char* vertexCode, const char* fragmentCode);

    bool use() const;

private:

    GLuint m_id = 0;

};
