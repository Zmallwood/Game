#include "Camera.h"
#include "../../../world_structure/Tile.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "core/Player.h"
#include "core/configuration/GameProps.h"
#include "core/rendering/CameraGL.h"

namespace zw
{
  void Camera::Update()
  {
    SetPerspectiveMatrix();
    SetViewMatrix();
  }

  void Camera::AddHorizontalAngleDelta(float delta)
  {
    m_horizontalAngleDegrees += delta;
  }

  void Camera::AddVerticalAngleDelta(float delta)
  {
    m_verticalAngleDegrees += delta;
  }

  void Camera::SetPerspectiveMatrix()
  {
    auto fovRads = glm::radians(m_usedFov / 2);
    auto aspect = 1600.0f / 900.0f;
    auto zNear = 0.1f;
    auto zFar = 3000.0f;
    auto newPerspMat = glm::perspective(fovRads, aspect, zNear, zFar);
    CameraGL::Get()->SetPerspectiveMatrix(newPerspMat);
  }

  void Camera::SetViewMatrix()
  {
    auto playerPos = Player::Get()->Position().Multiply(GameProps::Get()->TileSize());
    auto tileSize = GameProps::Get()->TileSize();
    auto currWA = World::Get()->WorldArea();
    auto lookFrom = GetCameraPosition();
    auto lookAt = playerPos;
    auto worldArea = World::Get()->WorldArea();
    auto playerTile = worldArea->GetTile(Player::Get()->Position().GetXZ().ToIntPoint());
    auto elev = playerTile->Elevation() * GameProps::Get()->ElevationScale();
    auto playrElev = elev;
    lookAt.y = playrElev;
    //lookFrom.z = lookAt.z + 50.0f;
    auto newViewMatrix = glm::lookAt(glm::vec3(lookFrom.x, lookFrom.y, lookFrom.z),
                                     glm::vec3(lookAt.x, lookAt.y, lookAt.z),
                                     glm::vec3(0.0, 1.0, 0.0));
    CameraGL::Get()->SetViewMatrix(newViewMatrix);
  }

  Point3F Camera::GetCameraPosition()
  {
    auto player = Player::Get();
    auto playerPos = player->Position().GetXZ();
    auto currWA = World::Get()->WorldArea();
    auto tileCoord = playerPos.ToIntPoint();
    auto tile = currWA->GetTile(tileCoord);
    float elev00 = 0.0f;
    float elev10 = elev00;
    float elev11 = elev00;
    float elev01 = elev00;
    auto coord10 = tileCoord.Translate(1, 0);
    auto coord11 = tileCoord.Translate(1, 1);
    auto coord01 = tileCoord.Translate(0, 1);

    if (currWA->ValidCoordinate(coord10))
    {
      elev10 = 0.0f;
    }

    if (currWA->ValidCoordinate(coord11))
    {
      elev11 = 0.0f;
    }

    if (currWA->ValidCoordinate(coord01))
    {
      elev01 = 0.0f;
    }

    auto tileAvgElev = (elev00 + elev10 + elev01 + elev11) / 4.0f;
    auto playerTileDx = playerPos.x - static_cast<int>(playerPos.x) - 0.5f;
    auto playerTileDy = playerPos.y - static_cast<int>(playerPos.y) - 0.5f;
    auto elevDx = ((elev10 - elev00) + (elev11 - elev01)) / 2.0f;
    auto elevDy = ((elev01 - elev00) + (elev11 - elev10)) / 2.0f;
    auto playerElev = tileAvgElev + playerTileDx * elevDx + playerTileDy * elevDy;
    auto elevAmount = 1.0f;
    auto playerPosNoElev = player->Position().Multiply(GameProps::Get()->TileSize());
    //playerPosNoElev.y = 0.0f;
    auto usedVertAngle = m_verticalAngleDegrees;
    float usedCamDist;
    usedCamDist = m_cameraDistance * 2.0f;
    auto dzUnrotated = CosDegrees(usedVertAngle) * usedCamDist;
    dzUnrotated = usedCamDist;
    auto hypotenuse = dzUnrotated * 50.0f;
    auto dx = SinDegrees(m_horizontalAngleDegrees) * hypotenuse - 3.0f * SinDegrees(m_horizontalAngleDegrees);
    auto dz = CosDegrees(m_horizontalAngleDegrees) * hypotenuse - 3.0f * CosDegrees(m_horizontalAngleDegrees);
    //auto dy = -1 * SinDegrees(usedVertAngle) * usedCamDist * 3.0f;
    auto hypo2 = std::sqrt(dx * dx + dz * dz);
    auto dy = -1 * SinDegrees(usedVertAngle) * hypo2;
    auto playrElev = 0.0f;
    auto worldArea = World::Get()->WorldArea();
    auto playerTile = worldArea->GetTile(Player::Get()->Position().GetXZ().ToIntPoint());
    auto elev = playerTile->Elevation() * GameProps::Get()->ElevationScale();
    playrElev = elev;
    {
      auto result = Point3F();

      if (m_useFixedCameraDistance)
      {
        result = playerPosNoElev.Translate(dx, dy + k_fixedCameraDistance, dz);
      }
      else
      {
        result = playerPosNoElev.Translate(dx, dy + playrElev, dz);
      }
      return result.Translate(0.0f, m_cameraHeight * 2.0f, 0.0f);
      //return result.Translate(0.0f, m_cameraHeight * 2.0f + 20.0f, 0.0f);
    }
  }

  Camera* Camera::Get()
  {
    static Camera instance;
    return &instance;
  }
}