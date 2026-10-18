#include "shader.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

shader::~shader() {
    if (m_ID) glDeleteProgram(m_ID);
}

bool shader::loadFromFile(const char* vertexPath, const char* fragmentPath) {

    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {

        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    } catch (std::ifstream::failure& e) {

        std::cout << "WARNING: Failed to read shader files, no changes were made:\n- Vertex: " << vertexPath << "\n- Fragment: " << fragmentPath << '\n';
        return false;
    }

    return loadFromText(vertexCode.c_str(), fragmentCode.c_str());
}

bool shader::loadFromText(const char* vertexCode, const char* fragmentCode) {
    if (vertexCode == nullptr || fragmentCode == nullptr) {
        std::cout << "WARNING: No shader source code provided, no changes were made.\n";
        return false;
    }

    GLuint vertex = 0;
    GLuint fragment = 0;

    int success;
    char infoLog[512];

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "ERROR: Vertex shader compilation failed: " << infoLog << "\n";
        glDeleteShader(vertex);
        return false;
    }

    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "ERROR: Fragment shader compilation failed: " << infoLog << "\n";
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return false;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR: Linking shader programs failed: " << infoLog << "\n";
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(program);
        return false;
    }

    if (m_ID != 0) {
        std::cout << "WARNING: Shader already created, overwriting.\n";
        glDeleteProgram(m_ID);
    }
    m_ID = program;

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

void shader::use() const {
    if (m_ID) glUseProgram(m_ID);
}