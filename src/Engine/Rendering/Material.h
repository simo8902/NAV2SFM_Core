//
// Created by Simeon on 9/27/2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm.hpp"
#include <string>
#include <iostream>
#include <filesystem>
#include "Shader.h"

#include "AssetItem.h"


class Material: public AssetItem  {
public:
    Material(const std::string& filePath)
        : AssetItem(std::filesystem::path(filePath).stem().string(), AssetType::Material, std::filesystem::path(filePath).parent_path().string()) {
        uuid = uuidGenerator();
        uuidStr = boost::uuids::to_string(uuid);
        std::cout << "[Material] Material created: " << name << " with UUID: " << uuidStr << std::endl;
    }

    std::string getName() const { return name; }
    std::string getUUID() const { return uuidStr; }

    void assignShader(const std::shared_ptr<Shader>& newShader) {
        shader = newShader;
        std::cout << "[Material] Assigned new shader: " << shader->getName() << std::endl;;
    }

    std::shared_ptr<Shader> getShader() const { return shader; }


    std::string name;

private:
    std::string uuidStr;
    boost::uuids::uuid uuid;
    std::shared_ptr<Shader> shader;
    static boost::uuids::random_generator uuidGenerator;

};

#endif //MATERIAL_H
