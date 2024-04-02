#include "ModelBank.h"
#include "model_structure/Model.h"

namespace zw
{
  ModelBank::ModelBank()
  {
    LoadAllModels();
  }

  std::string
  ModelBank::GetModelName(int modelNameHash)
  {
    if (m_modelNames.contains(modelNameHash))
    {
      return m_modelNames.at(modelNameHash);
    }
    return "";
  }

  void
  ModelBank::LoadAllModels()
  {
    using iterator = std::filesystem ::recursive_directory_iterator;
    auto allModelsPath = std::filesystem::current_path().string() + "/" + k_relModelsPath;

    for (auto& entry : iterator(allModelsPath))
    {
      auto absPath = entry.path().string();

      if (FileExtension(absPath) != "dae")
      {
        continue;
      }

      auto model = LoadSingleModel(absPath);
      auto modelName = FilenameNoExtension(absPath);
      auto modelNameHash = Hash(modelName);
      m_models[modelNameHash] = model;
      m_modelNames[modelNameHash] = modelName;
    }
  }

  std::shared_ptr<Model>
  ModelBank::LoadSingleModel(const std::string& absFilePath)
  {
    auto modelID = std::make_shared<Model>(absFilePath);

    return modelID;
  }

  std::shared_ptr<Model>
  ModelBank::GetModel(int modelNameHash)
  {
    for (auto model : m_models)
      if (model.first == modelNameHash)
        return model.second;

    return nullptr;
  }

  ModelBank*
  ModelBank::Get()
  {
    static ModelBank instance;                  // Create singleton instance once
    return &instance;
  }
}