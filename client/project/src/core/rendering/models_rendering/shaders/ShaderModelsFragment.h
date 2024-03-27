#pragma once

namespace Zmallwood
{
  inline static const GLchar* defaultShaderModelsFragment =
    R"(
    #version 330 core
    out vec4 FragColor;

    vec3 light_direction = -vec3(10.0, -5.5, 14.5)*5;
    vec3 light_ambient = vec3(4.65, 3.65, 2.65)/4.0;
    vec3 light_color = vec3(0.6, 0.6, 0.5);
    vec3 light_direction2 = -vec3(-14, 1.3, -10.5);
    vec3 light_color2 = vec3(0.8, 0.7, 0.6)*5.0;

    in vec2 TexCoords;
    in vec3 ex_Normal;
    in vec3 FragPos;  

    uniform sampler2D texture_diffuse1;
    uniform vec3 viewPos;
    uniform vec3 fogColor; 

    float nearPlane = 190.0;
    float farPlane = 265.0;

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

    void main()
    {    
        vec4 result;
        vec3 mAmbient = light_ambient * texture(texture_diffuse1, TexCoords).rgb;

        vec3 norm = normalize(ex_Normal);
        vec3 lightDir =normalize(-light_direction);
        float diff =  0.3*dot(norm, lightDir);
        vec3 mDiffuse = light_color * diff * texture(texture_diffuse1, TexCoords).rgb;
        vec3 lightDir2 =normalize(-light_direction2);
        float diff2 =  0.3*dot(norm, lightDir2);
        vec3 mDiffuse2 = light_color2 * diff2 * texture(texture_diffuse1, TexCoords).rgb;


        result.rgb = mAmbient + mDiffuse + mDiffuse2;
        result.a = texture(texture_diffuse1, TexCoords).a;

        FragColor = result;
        //FragColor = texture(texture_diffuse1, TexCoords);
        //

        if (fogColor == vec3(1.0, 1.0, 1.0))
            return;
        float d = distance(viewPos, FragPos);
        float fogFactor = getFogFactor(d, nearPlane, farPlane);
        float alpha = getFogFactorAlpha(d, nearPlane, farPlane);

        FragColor = mix(FragColor, vec4(fogColor, 1.0f), fogFactor);
        FragColor.a = 1-alpha;   
    }
)";
}