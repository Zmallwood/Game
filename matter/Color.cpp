#include "Color.h"
#include "ColorF.h"

namespace zw
{
  ColorF
  Color::ToColorF()
  {
    //std::cout << static_cast<float>(b) /255.0f<< std::endl;
    return { static_cast<float>(r) / 255.0f,
             static_cast<float>(g) / 255.0f,
             static_cast<float>(b) / 255.0f,
             static_cast<float>(a) / 255.0f };
  }
}