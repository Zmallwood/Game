#pragma once

namespace zw
{
  class AssimpNodeData
  {
  public:
    glm::mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<AssimpNodeData> children;
  };
}