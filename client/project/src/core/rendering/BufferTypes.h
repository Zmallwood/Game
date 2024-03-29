#pragma once

namespace Zmallwood
{
  /**
   * \brief Available buffer types for the renderers
  */
  enum class BufferTypes
  {
    Indices,
    Positions2D,
    Positions3D,
    Colors,
    Uvs,
    Normals,
    BoneIDs,
    Weights,
    Misc
  };
}