#include "ModelRenderer.h"

namespace Zmallwood {
  ModelRenderer *ModelRenderer::Get() {
    static ModelRenderer instance;
    return &instance;
  }
}