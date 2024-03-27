#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <numeric>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stb/stb_image.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "../../../matter/Color.h"
#include "../../../matter/ColorF.h"
#include "../../../matter/Size.h"
#include "../../../matter/Point.h"
#include "../../../matter/PointF.h"
#include "../../../matter/Point3F.h"
#include "../../../matter/Vertex3F.h"
#include "../../../matter/GLMVertex.h"
#include "common/Utilities.h"
#include "common/Square.h"
#include "common/AssimpGLMUtilities.h"
#include "core/core_math/Trigonometry.h"
#include "core/configuration/Constants.h"