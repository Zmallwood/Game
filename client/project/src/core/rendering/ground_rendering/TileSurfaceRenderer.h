#pragma once
#include "core/rendering/RendererBase.h"

namespace zw
{
  /**
   * \brief Renders whole tile surfaces (WorldAreas)
  */
  class TileSurfaceRenderer : public RendererBase
  {
  public:
    /**
     * \brief Cleanup used GL resources on destruction
    */
    ~TileSurfaceRenderer();

    /**
     * \brief Allocates resources for a new tile surface and returns VAO id
     * 
     * \return Vertex Array Object id for the created tile surface
    */
    GLuint NewTileSurface();

    /**
     * \brief Sets geometry data for previously created tile surface
     * 
     * \param VAOID VAO id for which tile surface to set the geomtry for
     * \param verts Vertex data for the tile surface
    */
    void SetTileSurfaceGeom(GLuint VAOID, std::vector<std::vector<Square<Vertex3F>>>& verts);

    /**
     * \brief Draw tile surface with provided VAO id using provided imege name for all tiles
    */
    void DrawTileSurface(const std::string& imageName, GLuint VAOID, bool depthTestOff = false);

    /**
     * \brief Returns singleton instance
     * 
     * \return Singleton instance
    */
    static TileSurfaceRenderer* Get();

    static constexpr int k_locPosition = 0;     ///< Shader location of position
    static constexpr int k_locColor = 1;        ///< Shader location of color
    static constexpr int k_locUv = 2;           ///< Shader location of UV
    static constexpr int k_locNormal = 3;       ///< Shader location of normal
    Color k_fogColorGround =                    ///< Color of fog appearing far away from the player
      { .r = 0, .g = 150, .b = 255 };

  private:
    /**
     * \biref Private constructor to force use singleton instance
    */
    TileSurfaceRenderer();

    int m_locProjection = -1;                   ///< Shader location of projection matrix
    int m_locView = -1;                         ///< Shader location of view matrix 
    int m_locModel = -1;                        ///< Shader location of model matrix 
    int m_locViewPos = -1;                      ///< Shader loation of view position matrix 
    int m_locFogColor = -1;                     ///< Shader location of fog color vector 
  };
}