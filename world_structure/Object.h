#pragma once

namespace Zmallwood
{
  class Object
  {
  public:
    Object(const std::string& typeName);
    auto Type() { return m_type; }

  private:
    int m_type = 0;
  };
}