#pragma once

namespace zw
{
  /**
   * \brief Contains utility functions for Assimp -> GLM conversion.
  */
  class AssimpGLMUtilities
  {
  public:
    /**
     * \brief Converts assimp matrix to GLM matrix
     * 
     * \param from Assimp matrix to be converted
     * 
     * \return Converted GLM maatrix
    */
    static glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from);
    
    /**
     * \brief Convert assimp vector to GLM vector.
     * 
     * \param from Assimp vector to be converetd.
     * 
     * \return Converted GLM vector.
    */
    static glm::vec3 GetGLMVec(const aiVector3D& from);
    
    /**
     * \brief Convert assimp quaternion to GLM quaternion
     * 
     * \param from Assimp quaternion to be converted.
     * 
     *  \return Converted GLM quaternion.
    */
    static glm::quat GetGLMQuat(const aiQuaternion& from);
  };
}