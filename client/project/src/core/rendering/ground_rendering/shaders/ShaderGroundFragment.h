#pragma once

namespace zw
{
  inline static const GLchar* shaderGroundFragment =                  ///< Frag shader for ground rendering
    R"(
    #version 330 core
    precision mediump float;

    vec3 light_direction = vec3(2.5, -18.0, -2.5)/1.0;
    vec3 light_ambient = vec3(9.8, 9.8, 9.8)/13.0;
    vec3 light_color = vec3(0.5, 0.5, 0.5)*2.0;

    in vec4 ex_Color;
    in vec2 ex_TexCoord;
    in vec3 ex_Normal;
    in vec3 FragPos;
    uniform sampler2D TexUnit;
    uniform vec3 viewPos;
    uniform vec3 fogColor;

    out vec4 fragColor;

    float nearPlane = 290.0;
    float farPlane = 365.0;

    float getFogFactor(float d, float nearPlane, float farPlane) {
        float FogMax = 1.0f * farPlane;
        float FogMin = 0.5f * farPlane;
        if (d>=FogMax) return 1.0f;
        if (d<=FogMin) return 0.0f;
        return 1.0f - (FogMax - d) / (FogMax - FogMin);
    }

    float getFogFactorAlpha(float d, float nearPlane, float farPlane) {
        float FogMax = 1.0f * farPlane;
        float FogMin = 0.7f * farPlane;
        if (d>=FogMax) return 1.0f;
        if (d<=FogMin) return 0.0f;
        return 1.0f - (FogMax - d) / (FogMax - FogMin);
    }

    void main() {
        vec4 color = vec4(ex_Color.rgb, texture(TexUnit, ex_TexCoord).a);

        if (color.a == 0.0)
            discard;

        vec3 mAmbient = light_ambient * texture(TexUnit, ex_TexCoord).rgb;
        vec3 norm = normalize(ex_Normal);
        vec3 lightDir = normalize(-light_direction);
        float diff = 3.5*max(dot(norm, lightDir), 0.15);
        vec3 mDiffuse = light_color * diff * texture(TexUnit, ex_TexCoord).rgb;
        vec3 result = mAmbient + mDiffuse;
        vec4 result2 = vec4(result.r*color.r, result.g*color.g, result.b*color.b, color.a);
        fragColor = result2;
        if (fogColor == vec3(1.0, 1.0, 1.0))
            return;
        float d = distance(viewPos, FragPos);
        float fogFactor = getFogFactor(d, nearPlane, farPlane);
        float alpha = getFogFactorAlpha(d, nearPlane, farPlane);

        fragColor = mix(fragColor, vec4(fogColor, 1.0f), fogFactor);
        fragColor.a = 1-alpha;

    }
    )";
}