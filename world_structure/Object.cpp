#include "Object.h"

namespace zw
{
  Object::Object(const std::string& typeName)
    : m_type(Hash(typeName))
  {
  }
}