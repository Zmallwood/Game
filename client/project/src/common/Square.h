#pragma once

namespace zw
{
  /**
   * \brief Four cornered square of provided type.
  */
  template<class T>
  class Square
  {
  public:
    /**
     * \brief Set all corners to same provided value.
     * 
     * \param value Value to apply to all four corners.
    */
    void SetAll(T value) { _00 = _01 = _11 = _10 = value; }

    T _00;
    T _01;
    T _11;
    T _10;
  };
}