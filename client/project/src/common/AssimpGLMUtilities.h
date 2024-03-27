#pragma once

namespace Zmallwood {
  class AssimpGLMUtilities {
   public:
    static glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4 &from);
    static glm::vec3 GetGLMVec(const aiVector3D &vec);
    static glm::quat GetGLMQuat(const aiQuaternion &pOrientation);
  };
}