#include "WorldViewRenderer.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "../../../world_structure/Tile.h"
#include "core/GameProps.h"
#include "core/rendering/ground_rendering/TileSurfaceRenderer.h"
#include "Camera.h"

namespace Zmallwood {
    void WorldViewRenderer::Initialize() {
        auto worldArea = World::Get()->WorldArea();
        std::vector<std::vector<Square<Vertex3F>>> surfVerts;
        auto tileSize = GameProps::Get()->TileSize();

        for (auto x = 0; x < worldArea->Width(); x++) {
            surfVerts.push_back(std::vector<Square<Vertex3F>>());
            for (auto y = 0; y < worldArea->Height(); y++) {
                Square<Vertex3F> verts;
                auto tile = worldArea->GetTile({.x = x, .y = y});

                verts._00.position = {x * tileSize, 0.0f - 0.0f, y * tileSize};
                verts._10.position = {x * tileSize + tileSize, 0.0f - 0.0f,
                                      y * tileSize};
                verts._11.position = {x * tileSize + tileSize, 0.0f - 0.0f,
                                      y * tileSize + tileSize};
                verts._01.position = {x * tileSize, 0.0f,
                                      y * tileSize + tileSize};
                verts._00.uv = {0.0f, 0.0f};
                verts._10.uv = {1.0f, 0.0f};
                verts._11.uv = {1.0f, 1.0f};
                verts._01.uv = {0.0f, 1.0f};
                verts._00.color = tile->Color().ToColorF();
                verts._10.color = tile->Color().ToColorF();
                verts._11.color = tile->Color().ToColorF();
                verts._01.color = tile->Color().ToColorF();
                verts._00.normal = {0.0f, 1.0f, 0.0f};
                verts._10.normal = {0.0f, 1.0f, 0.0f};
                verts._11.normal = {0.0f, 1.0f, 0.0f};
                verts._01.normal = {0.0f, 1.0f, 0.0f};
                surfVerts.at(x).push_back(verts);
            }
        }
        m_tileSurfaceID = TileSurfaceRenderer::Get()->NewTileSurface();
        TileSurfaceRenderer::Get()->SetTileSurfaceGeom(m_tileSurfaceID, surfVerts);
    }

    void WorldViewRenderer::UpdateCamera() {
        Camera::Get()->Update();
    }

    void WorldViewRenderer::RenderWorldView() {
        TileSurfaceRenderer::Get()->DrawTileSurface("Ground", m_tileSurfaceID);
    }

    WorldViewRenderer *WorldViewRenderer::Get() {
        static WorldViewRenderer instance;
        return &instance;
    }
}