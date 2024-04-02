#pragma once

namespace zw
{
  class Point
  {
  public:
    Point Translate(int dx, int dy) const { return { x + dx, y + dy }; }

    int x = 0;
    int y = 0;
  };
}