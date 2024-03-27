#pragma once

namespace Zmallwood {
  class AnimationBank {
   public:
    static AnimationBank *Get();

   private:
    AnimationBank() = default;
  };
}