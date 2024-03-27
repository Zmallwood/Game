#pragma once
#include "KeyPosition.h"
#include "KeyRotation.h"
#include "KeyScale.h"

namespace Zmallwood
{
  class Bone
  {
  public:
    Bone (const std::string &name, int ID, const aiNodeAnim *channel);
    void Update (float animationTime);
    int GetPositionIndex (float animationTime);
    int GetRotationIndex (float animationTime);
    int GetScaleIndex (float animationTime);

    auto LocalTransform () const { return m_localTransform; }

    std::string BoneName () const { return m_name; }

    int BoneID () const { return m_ID; }

  private:
    float GetScaleFactor (float lastTimeStamp, float nextTimeStamp,
                          float animationTime);
    glm::mat4 InterpolatePosition (float animationTime);
    glm::mat4 InterpolateRotation (float animationTime);
    glm::mat4 InterpolateScaling (float animationTime);

    std::vector<KeyPosition> m_positions;
    std::vector<KeyRotation> m_rotations;
    std::vector<KeyScale> m_scales;
    int m_numPositions;
    int m_numRotations;
    int m_numScalings;
    glm::mat4 m_localTransform;
    std::string m_name;
    int m_ID;
  };
}