#pragma once

namespace Zmallwood
{
  /**
   * \brief Returns ticks as milliseconds.
  */
  int Ticks();

  /**
   * \brief Creates hash code for provided string.
   * 
   * \param text Text to create hash code from.
  */
  int Hash(const std::string& text);
}