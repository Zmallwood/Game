#include "Object.h"

namespace Zmallwood
{
  Object::Object(const std::string& typeName)
    : m_type(Hash(typeName))
  {
  }
}