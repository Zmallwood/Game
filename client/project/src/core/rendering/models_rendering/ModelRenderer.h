#pragma once

namespace Zmallwood
{
  class ModelRenderer
  {
  public:
    static ModelRenderer* Get();

  private:
    ModelRenderer() = default;
  };
}