#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class shader {
public:

    shader() = default;
    ~shader();

    shader(const shader&) = delete;
    shader& operator=(const shader&) = delete;

    shader(shader&& other) noexcept {
        m_ID = other.m_ID;
        other.m_ID = 0;
    }
    shader& operator=(shader&& other) {
        if (this != &other) {
            if (m_ID)
                glDeleteProgram(m_ID);
            m_ID = other.m_ID;
            other.m_ID = 0;
        }
        return *this;
    }

    bool loadFromFile(const char* vertexPath, const char* fragmentPath);
    bool loadFromText(const char* vertexCode, const char* fragmentCode);

    void use() const;

private:

    GLuint m_ID = 0;

};
