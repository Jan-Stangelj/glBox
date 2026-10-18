#version 460 core

layout(binding = 0, std430) readonly buffer verticesBuffer {
    vec4 vertices[];
};
layout(binding = 1, std430) readonly buffer indicesBuffer {
    uint indices[];
};

void main() {
    gl_Position = vec4(vertices[indices[gl_VertexID]].xyz, 1.0);
}