#pragma once

namespace Zmallwood
{
  class ModelBank
  {
  public:
    static ModelBank* Get();

  private:
    ModelBank() = default;
  };
}