#include "WorldViewRenderer.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "../../../world_structure/Tile.h"
#include "core/configuration/GameProps.h"
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

        auto elev00 = tile->Elevation();
        auto elev10 = elev00;
        auto elev11 = elev00;
        auto elev01 = elev00;
        auto normal00 = tile->Normal();
        auto normal10 = normal00;
        auto normal11 = normal00;
        auto normal01 = normal00;

        if (x < worldArea->Width() - 1) {
          elev10 = worldArea->GetTile({.x = x + 1, .y = y})->Elevation();
          normal10 = worldArea->GetTile({.x = x + 1, .y = y})->Normal();
        }

        if (y < worldArea->Height() - 1) {
          elev01 = worldArea->GetTile({.x = x, .y = y + 1})->Elevation();
          normal01 = worldArea->GetTile({.x = x, .y = y + 1})->Normal();
        }

        if (x < worldArea->Width() - 1 && y < worldArea->Height() - 1) {
          elev11 = worldArea->GetTile({.x = x + 1, .y = y + 1})->Elevation();
          normal11 = worldArea->GetTile({.x = x + 1, .y = y + 1})->Normal();
        }

        auto elevAmount = 1.0f;

        verts._00.position = {x * tileSize, elev00 * elevAmount, y * tileSize};
        verts._10.position = {x * tileSize + tileSize, elev10 * elevAmount,
                              y * tileSize};
        verts._11.position = {x * tileSize + tileSize, elev11 * elevAmount,
                              y * tileSize + tileSize};
        verts._01.position = {x * tileSize, elev01 * elevAmount,
                              y * tileSize + tileSize};
        verts._00.uv = {0.0f, 0.0f};
        verts._10.uv = {1.0f, 0.0f};
        verts._11.uv = {1.0f, 1.0f};
        verts._01.uv = {0.0f, 1.0f};
        verts._00.color = tile->Color().ToColorF();
        verts._10.color = tile->Color().ToColorF();
        verts._11.color = tile->Color().ToColorF();
        verts._01.color = tile->Color().ToColorF();
        verts._00.normal = normal00;
        verts._10.normal = normal10;
        verts._11.normal = normal11;
        verts._01.normal = normal01;
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