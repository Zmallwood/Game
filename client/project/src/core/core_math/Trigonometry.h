#pragma once

namespace Zmallwood {
  inline float SinDegrees(float angleDegrees) {
    return sinf(angleDegrees * static_cast<float>(M_PI) / 180.0f);
  }

  inline float CosDegrees(float angleDegrees) {
    return cosf(angleDegrees * static_cast<float>(M_PI) / 180.0f);
  }
}