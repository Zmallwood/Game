#pragma once

namespace zw
{
  inline static const GLchar* shaderModelsVertex =
    R"(
    #version 430 core

    layout(location = 0) in vec3 pos;
    layout(location = 1) in vec3 norm;
    layout(location = 2) in vec2 tex;
    layout(location = 3) in ivec4 boneIds; 
    layout(location = 4) in vec4 weights;

    out vec3 ex_Normal;
    out vec3 FragPos;   
        
    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;
        
    const int MAX_BONES = 100;
    const int MAX_BONE_INFLUENCE = 4;
    uniform mat4 finalBonesMatrices[MAX_BONES];
        
    out vec2 TexCoords;
        
    void main()
    {
        vec4 totalPosition = vec4(0.0f);
        vec3 totalNormal = vec3(0.0f);
        for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
        {
            if(boneIds[i] == -1) 
                continue;
            if(boneIds[i] >=MAX_BONES) 
            {
                totalPosition = vec4(pos,1.0f);
                break;
            }
            vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos,1.0f);
            totalPosition += localPosition * weights[i];
            vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * norm;
            totalNormal += localNormal * weights[i];
        }
            
        mat4 viewModel = view * model;
        gl_Position =  projection * viewModel * totalPosition;
        TexCoords = tex;
        vec4 norm2 = vec4(totalNormal.x, totalNormal.y, totalNormal.z, 1.0f);
        mat4 m = model;
        // Remove translation
        m[3][0] = 0;
        m[3][1] = 0;
        m[3][2] = 0;
        vec4 modelNorm2 = m*norm2;
        ex_Normal = modelNorm2.xyz;
        FragPos = vec3(model * vec4(pos.x, pos.y, pos.z, 1.0));
    }
)";
}