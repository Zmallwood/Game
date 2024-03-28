#pragma once

namespace Zmallwood
{
  enum class BufferTypes                        // Different kinds of creatable buffers in RendererBase
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