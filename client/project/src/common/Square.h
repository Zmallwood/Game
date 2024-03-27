#pragma once

namespace Zmallwood {
  template <class T>
  class Square {
   public:
    void SetAll(T value) { _00 = _01 = _11 = _10 = value; }

    T _00;
    T _01;
    T _11;
    T _10;
  };
}