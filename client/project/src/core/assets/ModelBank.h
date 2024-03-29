#pragma once

namespace Zmallwood
{
  class Model;

  class ModelBank
  {
  public:
    std::shared_ptr<Model> GetModel(int modelNameHash);
    std::string GetModelName(int modelNameHash);
    auto &Models() {return m_models; }
    static ModelBank* Get();

  private:
    ModelBank();
    void LoadAllModels();
    std::shared_ptr<Model> LoadSingleModel(const std::string& absFilePath);

    const std::string k_relModelsPath = "resources/models/";
    std::map<int, std::shared_ptr<Model>> m_models;
    std::map<int, std::string> m_modelNames;
  };
}