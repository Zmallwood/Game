#include "Bone.h"

namespace Zmallwood
{
  Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel)
    : m_name(name)
    , m_ID(ID)
    , m_localTransform(1.0f)
  {
    m_numPositions = channel->mNumPositionKeys;

    for (int positionIndex = 0; positionIndex < m_numPositions; ++positionIndex)
    {
      aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
      float timeStamp = channel->mPositionKeys[positionIndex].mTime;
      KeyPosition data;
      data.position = AssimpGLMUtilities::GetGLMVec(aiPosition);
      data.timeStamp = timeStamp;
      m_positions.push_back(data);
    }

    m_numRotations = channel->mNumRotationKeys;

    for (int rotationIndex = 0; rotationIndex < m_numRotations; ++rotationIndex)
    {
      aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
      float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
      KeyRotation data;
      data.orientation = AssimpGLMUtilities::GetGLMQuat(aiOrientation);
      data.timeStamp = timeStamp;
      m_rotations.push_back(data);
    }

    m_numScalings = channel->mNumScalingKeys;

    for (int keyIndex = 0; keyIndex < m_numScalings; ++keyIndex)
    {
      aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
      float timeStamp = channel->mScalingKeys[keyIndex].mTime;
      KeyScale data;
      data.scale = AssimpGLMUtilities::GetGLMVec(scale);
      data.timeStamp = timeStamp;
      m_scales.push_back(data);
    }
  }

  void
  Bone::Update(float animationTime)
  {
    glm::mat4 translation = InterpolatePosition(animationTime);
    glm::mat4 rotation = InterpolateRotation(animationTime);
    glm::mat4 scale = InterpolateScaling(animationTime);
    m_localTransform = translation * rotation * scale;
  }

  int
  Bone::GetPositionIndex(float animationTime)
  {
    for (int index = 0; index < m_numPositions - 1; ++index)
      if (animationTime < m_positions[index + 1].timeStamp)
        return index;

    assert(0);
  }

  int
  Bone::GetRotationIndex(float animationTime)
  {
    for (int index = 0; index < m_numRotations - 1; ++index)
      if (animationTime < m_rotations[index + 1].timeStamp)
        return index;

    assert(0);
  }

  int
  Bone::GetScaleIndex(float animationTime)
  {
    for (int index = 0; index < m_numScalings - 1; ++index)
      if (animationTime < m_scales[index + 1].timeStamp)
        return index;

    assert(0);
  }

  float
  Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
  {
    float scaleFactor = 0.0f;
    float midWayLength = animationTime - lastTimeStamp;
    float framesDiff = nextTimeStamp - lastTimeStamp;
    scaleFactor = midWayLength / framesDiff;
    return scaleFactor;
  }

  glm::mat4
  Bone::InterpolatePosition(float animationTime)
  {
    if (1 == m_numPositions)
      return glm::translate(glm::mat4(1.0f), m_positions[0].position);

    int p0Index = GetPositionIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor =
      GetScaleFactor(m_positions[p0Index].timeStamp, m_positions[p1Index].timeStamp, animationTime);
    glm::vec3 finalPosition =
      glm::mix(m_positions[p0Index].position, m_positions[p1Index].position, scaleFactor);

    return glm::translate(glm::mat4(1.0f), finalPosition);
  }

  glm::mat4
  Bone::InterpolateRotation(float animationTime)
  {
    if (1 == m_numRotations)
    {
      auto rotation = glm::normalize(m_rotations[0].orientation);

      return glm::toMat4(rotation);
    }

    int p0Index = GetRotationIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor =
      GetScaleFactor(m_rotations[p0Index].timeStamp, m_rotations[p1Index].timeStamp, animationTime);
    glm::quat finalRotation =
      glm::slerp(m_rotations[p0Index].orientation, m_rotations[p1Index].orientation, scaleFactor);
    finalRotation = glm::normalize(finalRotation);

    return glm::toMat4(finalRotation);
  }

  glm::mat4
  Bone::InterpolateScaling(float animationTime)
  {
    if (1 == m_numScalings)
      return glm::scale(glm::mat4(1.0f), m_scales[0].scale);

    int p0Index = GetScaleIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor =
      GetScaleFactor(m_scales[p0Index].timeStamp, m_scales[p1Index].timeStamp, animationTime);
    glm::vec3 finalScale = glm::mix(m_scales[p0Index].scale, m_scales[p1Index].scale, scaleFactor);

    return glm::scale(glm::mat4(1.0f), finalScale);
  }
}