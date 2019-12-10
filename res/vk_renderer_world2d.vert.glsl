#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 texCoord;

vec2 positions[6] = vec2[](
    // Top-left triangle
    vec2(-1, -1),
    vec2( 1, -1),
    vec2(-1,  1),
    // Bottom-right triangle
    vec2( 1,  1),
    vec2(-1,  1),
    vec2( 1, -1)
);

vec3 colors[6] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0),
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 0.0, 1.0),
    vec3(0.0, 1.0, 0.0)
);

void main() {
    gl_Position = vec4(
	positions[gl_VertexIndex],
	0.0, 1.0
    );

    fragColor = colors[gl_VertexIndex];
    texCoord = positions[gl_VertexIndex];
}
