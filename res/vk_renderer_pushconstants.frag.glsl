#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 texCoord;

struct Intent { vec2 m; };
struct Aspect { float a; };

// TODO: FIXME
layout(push_constant, binding = 0) uniform PushConstants {
    Intent i;
    Aspect a;
} pc;

layout(location = 0) out vec4 outColor;

void main() {
    vec2 dff = {
      0.0625/(pc.a.a*(texCoord.x - pc.i.m.x)),
      // pc.a.a*(texCoord.x - pc.i.m.x),
      0.0625/(texCoord.y - pc.i.m.y)
      // (texCoord.y - pc.i.m.y)
    };

    float dst = dff.x*dff.x + dff.y*dff.y;

    outColor = vec4(dst*dst*fragColor, 1);

    /*
    vec4 outc = vec4(vec3(0.0), 1.0);
    if (abs(texCoord.x - pc.i.m.x) < 1.0/256.0) {
        outc.r = 1;
    }
    if (abs(texCoord.y - pc.i.m.y) < 1.0/256.0) {
        outc.r = 1;
    }
    if (dst < 1.0/64.0) {
        outc = 64*dst*vec4(1,1,1,1);
    }
    outColor = outc;
    */
}
