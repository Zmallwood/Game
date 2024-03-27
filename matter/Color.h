#pragma once

namespace Zmallwood
{
  class ColorF;

  class Color
  {
  public:
    ColorF ToColorF();

    unsigned char r = 255;
    unsigned char g = 255;
    unsigned char b = 255;
    unsigned char a = 255;
  };
}