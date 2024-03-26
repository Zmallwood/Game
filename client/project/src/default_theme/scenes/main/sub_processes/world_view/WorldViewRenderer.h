#pragma once

namespace Zmallwood {
    class WorldViewRenderer {
       public:
        void Initialize();
        void UpdateCamera();
        void RenderWorldView();
        static WorldViewRenderer *Get();

       private:
        WorldViewRenderer() = default;

        GLuint m_GLIDTileSurface = -1;
    };
}