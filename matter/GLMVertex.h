#pragma once
#include "core/configuration/Constants.h"

namespace Zmallwood {
  class GLMVertex {
   public:
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    // Bone indexes which will influence this vertex
    int m_boneIDs[k_maxBoneInfluence];
    // Weights from each bone
    float m_weights[k_maxBoneInfluence];
  };
}