#include "Trigonometry.h"

namespace zw
{
  float
  SinDegrees(float angleDegrees)
  {
    return sinf(                                // Convert angle to radians and calculate sin
      angleDegrees * static_cast<float>(M_PI) / 180.0f);
  }

  float
  CosDegrees(float angleDegrees)
  {
    return cosf(                                // Convert angle to radians and calculate cosinus
      angleDegrees * static_cast<float>(M_PI) / 180.0f);
  }
}