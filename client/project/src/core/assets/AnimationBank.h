#pragma once

namespace Zmallwood
{
  class Animation;
  class Animator;

  class AnimationBank
  {
  public:
    std::shared_ptr<Animator> GetAnimator(int animationNameHash, int modelNameHash);
    static AnimationBank* Get();

  private:
    AnimationBank() = default;
    bool CreateSingleAnimator(int animNameHash, int modelNameHash);

    const std::string k_relAnimationsPath = "resources/animations/";
    std::map<int, std::shared_ptr<Animation>> m_animations;
    std::map<int, std::map<int, std::shared_ptr<Animator>>> m_animators;
  };
}