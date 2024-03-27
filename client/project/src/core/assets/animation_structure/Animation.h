#pragma once
#include "AssimpNodeData.h"
#include "Bone.h"
#include "BoneInfo.h"

namespace Zmallwood
{
  class Model;

  class Animation
  {
   public:
    Animation (void) = default;
    Animation (const std::string &animationPath, Model *model);
    Bone *FindBone (const std::string &name);
    float TicksPerSecond () const { return m_ticksPerSecond; }
    float Duration () const { return m_duration; }
    const AssimpNodeData &RootNode () const { return m_rootNode; }
    const std::map<std::string, BoneInfo> &BoneIDMap () const
    {
      return m_boneInfoMap;
    }

   private:
    void ReadMissingBones (const aiAnimation *animation, Model &model);
    void ReadHierarchyData (AssimpNodeData &dest, const aiNode *src);

    float m_duration;
    int m_ticksPerSecond;
    std::vector<Bone> m_bones;
    AssimpNodeData m_rootNode;
    std::map<std::string, BoneInfo> m_boneInfoMap;
  };
}