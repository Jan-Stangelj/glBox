#version 460 core

layout(binding = 0, std430) readonly buffer vertices {
    vec4 data[];
};

void main() {
    gl_Position = vec4(data[gl_VertexID].xyz, 1.0);
}