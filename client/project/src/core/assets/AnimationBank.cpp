#include "AnimationBank.h"
#include "animation_structure/Animation.h"
#include "animation_structure/Animator.h"
#include "core/assets/ModelBank.h"

namespace Zmallwood
{
  std::shared_ptr<Animator>
  AnimationBank::GetAnimator(int animationNameHash, int modelNameHash)
  {
    if (m_animators.count(animationNameHash))
    {
      if (m_animators.at(animationNameHash).count(modelNameHash))
      {
        return m_animators.at(animationNameHash).at(modelNameHash);
      }
    }

    if (CreateSingleAnimator(animationNameHash, modelNameHash))
    {
      return m_animators[animationNameHash][modelNameHash];
    }
    else
    {
      return nullptr;
    }
  }

  bool
  AnimationBank::CreateSingleAnimator(int animationNameHash, int modelNameHash)
  {
    std::map<int, std::string> animationNames = { { Hash("AnimObjectTree1"), "AnimObjectTree1" } };

    auto animationName = animationNames.at(animationNameHash);

    auto absFilePath =
      std::filesystem::current_path().string() + k_relAnimationsPath + animationName + ".dae";

    if (std::filesystem::exists(absFilePath) == false)
    {
      return false;
    }

    auto newAnimation =
      std::make_shared<Animation>(absFilePath.data(), ModelBank::Get()->GetModel(modelNameHash).get());
    m_animations[animationNameHash] = newAnimation;
    auto newAnimator = std::make_shared<Animator>(newAnimation.get());
    m_animators[animationNameHash][modelNameHash] = newAnimator;

    return true;
  }

  AnimationBank*
  AnimationBank::Get()
  {
    static AnimationBank instance;              // Create singleton instance once
    return &instance;
  }
}