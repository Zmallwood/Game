#include "MouseButton.h"

namespace zw
{
  void
  MouseButton::OnPress()
  {
    m_pressed = true;                           // Button is pressed down
  }

  void
  MouseButton::OnRelease()
  {
    m_pressed = false;                          // Button is not pressed down
  }
}