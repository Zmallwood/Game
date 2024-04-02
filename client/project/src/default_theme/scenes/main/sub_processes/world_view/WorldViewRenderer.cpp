#include "WorldViewRenderer.h"
#include "../../../world_structure/Tile.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "../../../world_structure/TileTypeColors.h"
#include "Camera.h"
#include "core/configuration/GameProps.h"
#include "core/rendering/ground_rendering/TileRenderer.h"
#include "sub_processes/ObjectsRendering.h"
#include "sub_processes/PlayerRendering.h"

namespace zw
{
  void
  WorldViewRenderer::Initialize()
  {
    auto worldArea = World::Get()->WorldArea();
    auto surfVerts = std::vector<std::vector<Square<Vertex3F>>>();
    auto tileSize = GameProps::Get()->TileSize();
    auto elevScale = GameProps::Get()->ElevationScale();

    for (auto x = 0; x < worldArea->Width(); x++)
    {
      surfVerts.push_back(std::vector<Square<Vertex3F>>());
      for (auto y = 0; y < worldArea->Height(); y++)
      {
        Square<Vertex3F> verts;
        auto tile = worldArea->GetTile({ .x = x, .y = y });

        auto elev00 = tile->Elevation()*elevScale;
        auto elev10 = elev00;
        auto elev11 = elev00;
        auto elev01 = elev00;
        auto normal00 = tile->Normal();
        auto normal10 = normal00;
        auto normal11 = normal00;
        auto normal01 = normal00;

        if (x < worldArea->Width() - 1)
        {
          elev10 = worldArea->GetTile({ .x = x + 1, .y = y })->Elevation()*elevScale;
          normal10 = worldArea->GetTile({ .x = x + 1, .y = y })->Normal();
        }

        if (y < worldArea->Height() - 1)
        {
          elev01 = worldArea->GetTile({ .x = x, .y = y + 1 })->Elevation()*elevScale;
          normal01 = worldArea->GetTile({ .x = x, .y = y + 1 })->Normal();
        }

        if (x < worldArea->Width() - 1 && y < worldArea->Height() - 1)
        {
          elev11 = worldArea->GetTile({ .x = x + 1, .y = y + 1 })->Elevation()*elevScale;
          normal11 = worldArea->GetTile({ .x = x + 1, .y = y + 1 })->Normal();
        }

        auto elevAmount = 1.0f;

        verts._00.position = { x * tileSize, elev00 * elevAmount, y * tileSize };
        verts._10.position = { x * tileSize + tileSize, elev10 * elevAmount, y * tileSize };
        verts._11.position = { x * tileSize + tileSize, elev11 * elevAmount, y * tileSize + tileSize };
        verts._01.position = { x * tileSize, elev01 * elevAmount, y * tileSize + tileSize };
        verts._00.uv = { 0.0f, 0.0f };
        verts._10.uv = { 1.0f, 0.0f };
        verts._11.uv = { 1.0f, 1.0f };
        verts._01.uv = { 0.0f, 1.0f };
        auto tileType = tile->Type();
        auto typeColor = k_tileTypeColors.at(tileType);
        verts._00.color = typeColor.ToColorF();
        verts._10.color = typeColor.ToColorF();
        verts._11.color = typeColor.ToColorF();
        verts._01.color = typeColor.ToColorF();
        verts._00.normal = normal00;
        verts._10.normal = normal10;
        verts._11.normal = normal11;
        verts._01.normal = normal01;
        surfVerts.at(x).push_back(verts);
      }
    }
    m_tileSurfaceID = TileRenderer::Get()->NewTileSurface();
    TileRenderer::Get()->SetTileSurfaceGeom(m_tileSurfaceID, surfVerts);
  }

  void
  WorldViewRenderer::UpdateCamera()
  {
    Camera::Get()->Update();
  }

  void
  WorldViewRenderer::RenderWorldView()
  {
    TileRenderer::Get()->DrawTileSurface("Ground", m_tileSurfaceID);
    RenderObjects();
    RenderPlayer();
  }

  WorldViewRenderer*
  WorldViewRenderer::Get()
  {
    static WorldViewRenderer instance;
    return &instance;
  }
}