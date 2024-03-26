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

#include "../../../matter/Color.h"
#include "../../../matter/GLColor.h"
#include "../../../matter/Size.h"
#include "../../../matter/Point.h"
#include "../../../matter/PointF.h"
#include "../../../matter/Point3F.h"
#include "../../../matter/Vertex3F.h"
#include "common/Utilities.h"
#include "common/Square.h"
#include "core//core_math/Trigonometry.h"