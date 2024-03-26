#pragma once
#include "core/rendering/RendererBase.h"

namespace Zmallwood {
    class GroundRenderer : public RendererBase {
       public:
        ~GroundRenderer();
        GLuint NewTile();
        GLuint NewTileSurface();
        void DeleteTileSurface(GLuint GLID);
        void SetTileGeom(GLuint VAOID, Square<Vertex3F> &verts);
        void SetTileSufaceGeom(
            GLuint VAOID, std::vector<std::vector<Square<Vertex3F>>> &verts);
        void DrawTileSurface(const std::string &imageName, GLuint VAOID,
                             bool depthTestOff = false);
        void DrawTile(const std::string &imageName, GLuint VAOID,
                      bool depthTestOff = false);
        void StartTileBatchDrawing();
        void StopTileBatchDrawing();
        auto LocProjection() { return m_locProjection; }
        static GroundRenderer *Get();

        static constexpr int k_locPosition = 0;
        static constexpr int k_locColor = 1;
        static constexpr int k_locUv = 2;
        static constexpr int k_locNormal = 3;
        Color k_fogColorGround = {.r = 0, .g = 150, .b = 255};

       private:
       private:
        GroundRenderer();

        int m_locProjection = -1;
        int m_locView = -1;
        int m_locModel = -1;
        int m_locAlpha = -1;
        int m_locViewPos = -1;
        int m_locFogColor = -1;
        bool m_isBatchDrawing = false;
    };
}