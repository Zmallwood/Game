#include "Animation.h"
#include "core/assets/model_structure/Model.h"

namespace Zmallwood {
  Animation::Animation(const std::string &animationPath, Model *model) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(animationPath,
                                             aiProcess_Triangulate);
    assert(scene && scene->mRootNode);
    auto animation = scene->mAnimations[0];
    m_duration = animation->mDuration;
    m_ticksPerSecond = animation->mTicksPerSecond;
    aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
    globalTransformation = globalTransformation.Inverse();
    ReadHierarchyData(m_rootNode, scene->mRootNode);
    ReadMissingBones(animation, *model);
  }

  Bone *Animation::FindBone(const std::string &name) {
    auto iter = std::find_if(
        m_bones.begin(), m_bones.end(),
        [&](const Bone &Bone) { return Bone.BoneName() == name; });

    if (iter == m_bones.end())
      return nullptr;
    else
      return &(*iter);
  }

  void Animation::ReadMissingBones(const aiAnimation *animation, Model &model) {
    int size = animation->mNumChannels;
    auto &boneInfoMap =
        model.BoneInfoMap();  // getting m_BoneInfoMap from Model class
    int &boneCount =
        model.BoneCount();  // getting the m_boneCounter from Model class

    // reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++) {
      auto channel = animation->mChannels[i];
      std::string boneName = channel->mNodeName.data;

      if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
        boneInfoMap[boneName].ID = boneCount;
        boneCount++;
      }

      m_bones.push_back(Bone(channel->mNodeName.data,
                             boneInfoMap[channel->mNodeName.data].ID, channel));
    }

    m_boneInfoMap = boneInfoMap;
  }

  void Animation::ReadHierarchyData(AssimpNodeData &dest, const aiNode *src) {
    assert(src);
    dest.name = src->mName.data;
    dest.transformation = AssimpGLMUtilities::ConvertMatrixToGLMFormat(
        src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++) {
      AssimpNodeData newData;
      ReadHierarchyData(newData, src->mChildren[i]);
      dest.children.push_back(newData);
    }
  }
}