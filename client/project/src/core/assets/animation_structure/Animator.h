#pragma once

namespace zw
{
  class Animation;
  class AssimpNodeData;

  class Animator
  {
  public:
    Animator(Animation* animation);
    void UpdateAnimation(float dt);
    void PlayAnimation(Animation* pAnimation);
    void CalculateBoneTransform(const AssimpNodeData* node,
                                glm::mat4 parentTransform);
    auto FinalBoneMatrices() const { return m_finalBoneMatrices; }
    void SetCurrentTime(float value) { m_currentTime = value; }
    void SetDisableAutomaticUpdating(bool value)
    {
      m_disableAutomaticUpdating = value;
    }

  private:
    std::vector<glm::mat4> m_finalBoneMatrices;
    Animation* m_currentAnimation;
    float m_currentTime;
    float m_deltaTime;
    bool m_disableAutomaticUpdating = false;
  };
}