#include "Animator.h"
#include "Animation.h"

namespace Zmallwood
{
  Animator::Animator(Animation* animation)
  {
    m_currentTime = 0.0;
    m_currentAnimation = animation;
    m_finalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
      m_finalBoneMatrices.push_back(glm::mat4(1.0f));
  }

  void
  Animator::UpdateAnimation(float dt)
  {
    m_deltaTime = dt;

    if (m_currentAnimation)
    {
      if (!m_disableAutomaticUpdating)
        m_currentTime += m_currentAnimation->TicksPerSecond() * dt;

      m_currentTime = fmod(m_currentTime, m_currentAnimation->Duration());
      CalculateBoneTransform(&m_currentAnimation->RootNode(), glm::mat4(1.0f));
    }
  }

  void
  Animator::PlayAnimation(Animation* pAnimation)
  {
    m_currentAnimation = pAnimation;
    m_currentTime = 0.0f;
  }

  void
  Animator::CalculateBoneTransform(const AssimpNodeData* node,
                                   glm::mat4 parentTransform)
  {
    std::string nodeName = node->name;
    glm::mat4 nodeTransform = node->transformation;
    Bone* Bone = m_currentAnimation->FindBone(nodeName);

    if (Bone)
    {
      Bone->Update(m_currentTime);
      nodeTransform = Bone->LocalTransform();
    }

    glm::mat4 globalTransformation = parentTransform * nodeTransform;
    auto boneInfoMap = m_currentAnimation->BoneIDMap();

    if (boneInfoMap.find(nodeName) != boneInfoMap.end())
    {
      int index = boneInfoMap[nodeName].ID;
      glm::mat4 offset = boneInfoMap[nodeName].offset;
      m_finalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->childrenCount; i++)
      CalculateBoneTransform(&node->children[i], globalTransformation);
  }
}