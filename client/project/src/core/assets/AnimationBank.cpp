#include "AnimationBank.h"
#include "animation_structure/Animation.h"
#include "animation_structure/Animator.h"
#include "core/assets/ModelBank.h"

namespace zw
{
  AnimationBank::AnimationBank()
  {
    ReadAnimationNames();
  }

  void
  AnimationBank::ReadAnimationNames()
  {
    using iterator = std::filesystem ::recursive_directory_iterator;
    auto allAnimationsPath = std::filesystem::current_path().string() + "/" + k_relAnimationsPath;

    for (auto& entry : iterator(allAnimationsPath))
    {
      auto absPath = entry.path().string();

      if (FileExtension(absPath) != "dae")
      {
        continue;
      }
      {
        auto animName = FilenameNoExtension(absPath);
        m_animationNames.insert({ Hash(animName), animName });
      }
    }
  }

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

  void
  AnimationBank::UpdateAllAnimations()
  {
    float currentFrame = Ticks() / 1000.0f;
    auto deltaTime = currentFrame - m_lastFrame;

    for (auto& animationEntry : m_animators)
    {
      for (auto& modelEntry : animationEntry.second)
      {
        auto& animator = modelEntry.second;
        animator->UpdateAnimation(deltaTime);
      }
    }

    m_lastFrame = currentFrame;
  }

  bool
  AnimationBank::CreateSingleAnimator(int animationNameHash, int modelNameHash)
  {
    auto animationName = m_animationNames.at(animationNameHash);

    auto absFilePath =
      std::filesystem::current_path().string() + "/" + k_relAnimationsPath + animationName + ".dae";

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