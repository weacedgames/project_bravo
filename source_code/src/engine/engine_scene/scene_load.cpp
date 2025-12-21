#include "scene_load.h"

std::vector<std::vector<std::string>> SceneLoad::loadEntities()
{
    std::vector<std::vector<std::string>> files;
    for (const auto& entry : std::filesystem::directory_iterator("./scene/entities"))
    {
        if(entry.is_regular_file())
        {   
            std::vector<std::string> file;
            std::ifstream file_read("./scene/entities/" + entry.path().filename().string());
            if(file_read.is_open())
            {
                std::string line;
                while(getline(file_read, line)){
                    file.push_back(line);
                }
                file_read.close();
            }
            else
            {
                std::cerr << "ERROR::ENTITIES::LOADING_ENTITY" << std::endl;
            }
            files.push_back(file);
        }
        else if(entry.is_directory())
        {
            for (const auto& subEntry : std::filesystem::directory_iterator("./scene/entities/" + entry.path().filename().string()) )
            {
                if(entry.is_regular_file())
                {
                    std::vector<std::string> file;
                    std::ifstream file_read("./scene/entities/" + entry.path().filename().string() + "/" + subEntry.path().filename().string());
                    
                    if(file_read.is_open())
                    {
                        std::string line;
                        while(getline(file_read, line)){
                            file.push_back(line);
                        }
                        file_read.close();
                    }
                    else
                    {
                        std::cerr << "ERROR::CLASS::LOADING_ENTITY" << std::endl;
                    }
                    files.push_back(file);
                }
                else if(entry.is_directory())
                {
                    for (const auto& subSubEntry : std::filesystem::directory_iterator("./scene/entities/" + entry.path().filename().string() + "/" + subEntry.path().filename().string()))
                    {
                        std::vector<std::string> file;
                        std::ifstream file_read("./scene/entities/" + entry.path().filename().string() + "/" + subEntry.path().filename().string() + "/" + subSubEntry.path().filename().string());
                        
                        if(file_read.is_open())
                        {
                            std::string line;
                            while(getline(file_read, line)){
                                file.push_back(line);
                            }
                            file_read.close();
                        }
                        else
                        {
                            std::cerr << "ERROR::SUBCLASS::LOADING_ENTITY" << std::endl;
                        }
                        files.push_back(file);
                    }
                }
            }
        }
    }
    return files;
};

std::vector<Entity*> SceneLoad::generateEntities(std::vector<std::vector<std::string>> files, std::vector<Shader*> loaded_shaders, std::vector<Model*> loaded_models, std::vector<Sprite*> loaded_sprites, std::vector<Geometry*> loaded_geometry, Camera* camera)
{
    std::vector<Entity*> entities;

    for(int index=0; index < files.size() ; index++)
    {

        std::string type = "";
        std::string name = "";
        std::string tag = "";

        std::string pathVertexShader = "";
        std::string pathFragmentShader = "";

        int shader_id = 0;
        int shader_boundingBox_id = -1;
        int model_id = 0;
        int sprite_id = 0;

        std::string pathImage = "";

        std::string geometryType = "";
        
        float colorRed = 0.0f;
        float colorGreen = 0.0f;
        float colorBlue = 0.0f;

        float xPos = 0.0f;
        float yPos = 0.0f;
        float zPos = 0.0f;

        float xScale = 0.0f;
        float yScale = 0.0f;
        float zScale = 0.0f;

        float xRotation = 0.0f;
        float yRotation = 0.0f;
        float zRotation = 0.0f;

        bool enableRender = false;
        bool enableBoundingBox = false;
        bool enableCollider = false;

        for(int subIndex=0; subIndex<files[index].size(); subIndex++)
        {
            size_t pos = files[index][subIndex].find('=');

            if(pos != std::string::npos)
            {
                std::string key = files[index][subIndex].substr(0, pos);
                std::string value = files[index][subIndex].substr(pos + 1);

                if(key=="TYPE")
                    type = value;
                if(key=="NAME")
                    name = value;
                if(key=="TAG")
                    tag = value;

                if(type=="camera")
                {
                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);
                }
                
                if(type=="model")
                {
                    if(key=="SHADERID")
                        shader_id = std::stoi(value);
                    if(key=="SHADERBOUNDINGBOXID")
                        shader_boundingBox_id = std::stoi(value);
                    if(key=="MODELID")
                        model_id = std::stoi(value);

                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);

                    if(key=="SCALEX")
                        xScale = std::stof(value);
                    if(key=="SCALEY")
                        yScale = std::stof(value);
                    if(key=="SCALEZ")
                        zScale = std::stof(value);

                    if(key=="ROTATIONX")
                        xRotation = std::stof(value);
                    if(key=="ROTATIONY")
                        yRotation = std::stof(value);
                    if(key=="ROTATIONZ")
                        zRotation = std::stof(value);

                    if(key=="ENABLERENDER")
                        enableRender = std::stoi(value);
                    if(key=="ENABLEBOUNDINGBOX")
                        enableBoundingBox = std::stoi(value);
                }

                if(type=="sprite")
                {
                    if(key=="SHADERID")
                        shader_id = std::stoi(value);
                    if(key=="SPRITEID")
                        sprite_id = std::stoi(value);

                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);

                    if(key=="SCALEX")
                        xScale = std::stof(value);
                    if(key=="SCALEY")
                        yScale = std::stof(value);
                    if(key=="SCALEZ")
                        zScale = std::stof(value);

                    if(key=="ROTATIONX")
                        xRotation = std::stof(value);
                    if(key=="ROTATIONY")
                        yRotation = std::stof(value);
                    if(key=="ROTATIONZ")
                        zRotation = std::stof(value);

                    if(key=="ENABLERENDER")
                        enableRender = std::stoi(value);
                    if(key=="ENABLEBOUNDINGBOX")
                        enableBoundingBox = std::stoi(value);
                }

                if(type=="geometry")
                {
                    if(key=="SHADERID")
                        shader_id = std::stoi(value);
                    if(key=="SHADERBOUNDINGBOXID")
                        shader_boundingBox_id = std::stoi(value);
                    if(key=="MODELID")
                        model_id = std::stoi(value);

                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);

                    if(key=="GEOMETRYTYPE")
                        geometryType = value;
                    if(key=="GEOMETRYCOLORRED")
                        colorRed = std::stof(value);
                    if(key=="GEOMETRYCOLORGREEN")
                        colorGreen = std::stof(value);
                    if(key=="GEOMETRYCOLORBLUE")
                        colorBlue = std::stof(value);

                    if(key=="SCALEX")
                        xScale = std::stof(value);
                    if(key=="SCALEY")
                        yScale = std::stof(value);
                    if(key=="SCALEZ")
                        zScale = std::stof(value);

                    if(key=="ROTATIONX")
                        xRotation = std::stof(value);
                    if(key=="ROTATIONY")
                        yRotation = std::stof(value);
                    if(key=="ROTATIONZ")
                        zRotation = std::stof(value);

                    if(key=="ENABLERENDER")
                        enableRender = std::stoi(value);
                    if(key=="ENABLEBOUNDINGBOX")
                        enableBoundingBox = std::stoi(value);
                    if(key=="ENABLECOLLIDER")
                        enableCollider = std::stoi(value);
                }

                if(type=="overlay")
                {

                    if(key=="SHADERID")
                        shader_id = std::stoi(value);
                    if(key=="SHADERBOUNDINGBOXID")
                        shader_boundingBox_id = std::stoi(value);
                    if(key=="MODELID")
                        model_id = std::stoi(value);


                    if(key=="POSITIONX")
                        xPos = std::stof(value);
                    if(key=="POSITIONY")
                        yPos = std::stof(value);
                    if(key=="POSITIONZ")
                        zPos = std::stof(value);

                    if(key=="SCALEX")
                        xScale = std::stof(value);
                    if(key=="SCALEY")
                        yScale = std::stof(value);
                    if(key=="SCALEZ")
                        zScale = std::stof(value);

                    if(key=="ROTATIONX")
                        xRotation = std::stof(value);
                    if(key=="ROTATIONY")
                        yRotation = std::stof(value);
                    if(key=="ROTATIONZ")
                        zRotation = std::stof(value);

                    if(key=="ENABLERENDER")
                        enableRender = std::stoi(value);
                    if(key=="ENABLEBOUNDINGBOX")
                        enableBoundingBox = std::stoi(value);
                }
                
            }
        }

        Entity* tempEntity = new Entity();

        if(type=="camera")
        {
            tempEntity->setCamera(camera);
            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            entities.push_back(tempEntity);
        }

        if(type=="model")
        {
            for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
            {
                if(shader_id == loaded_shaders[subIndex]->assetShaderId)
                    tempEntity->setShader(loaded_shaders[subIndex]);
            }

            if(shader_boundingBox_id != -1)
            {
                for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
                {
                    if(shader_boundingBox_id == loaded_shaders[subIndex]->assetShaderId)
                        tempEntity->setShaderBoundingBox(loaded_shaders[subIndex]);
                }
            }

            for(int subIndex=0; subIndex<loaded_models.size(); subIndex++)
            {
                if(model_id == loaded_models[subIndex]->assetModelID)
                    tempEntity->setModel(loaded_models[subIndex]);

            }

            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            tempEntity->setScale(glm::vec3(xScale, yScale, zScale));
            tempEntity->setRotation(glm::vec3( xRotation, yRotation, zRotation));
            tempEntity->setEnableRender(enableRender);
            tempEntity->setEnableBoundingBox(enableBoundingBox);
            entities.push_back(tempEntity);
        }

        



        if(type=="sprite")
        {
            for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
            {
                if(shader_id == loaded_shaders[subIndex]->assetShaderId)
                    tempEntity->setShader(loaded_shaders[subIndex]);
            }

            for(int subIndex=0; subIndex<loaded_sprites.size(); subIndex++)
            {
                if(sprite_id == loaded_sprites[subIndex]->assetSpriteID)
                {
                    tempEntity->setSprite(loaded_sprites[subIndex]);
                }
            }

            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            tempEntity->setScale(glm::vec3(xScale, yScale, zScale));
            tempEntity->setRotation(glm::vec3( xRotation, yRotation, zRotation));
            tempEntity->setEnableRender(enableRender);
            tempEntity->setEnableBoundingBox(enableBoundingBox);
            entities.push_back(tempEntity);
        }



        if(type=="overlay")
        {
            for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
            {
                if(shader_id == loaded_shaders[subIndex]->assetShaderId)
                    tempEntity->setShader(loaded_shaders[subIndex]);
            }

            if(shader_boundingBox_id != -1)
            {
                for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
                {
                    if(shader_boundingBox_id == loaded_shaders[subIndex]->assetShaderId)
                        tempEntity->setShaderBoundingBox(loaded_shaders[subIndex]);
                }
            }

            for(int subIndex=0; subIndex<loaded_models.size(); subIndex++)
            {
                if(model_id == loaded_models[subIndex]->assetModelID)
                    tempEntity->setModel(loaded_models[subIndex]);

            }
            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            tempEntity->setScale(glm::vec3(xScale, yScale, zScale));
            tempEntity->setRotation(glm::vec3( xRotation, yRotation, zRotation));
            tempEntity->setEnableRender(enableRender);
            tempEntity->setEnableBoundingBox(enableBoundingBox);
            entities.push_back(tempEntity);
        }

        if(type=="geometry")
        {
            for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
            {
                if(shader_id == loaded_shaders[subIndex]->assetShaderId)
                    tempEntity->setShader(loaded_shaders[subIndex]);
            }

            if(shader_boundingBox_id != -1)
            {
                for(int subIndex=0; subIndex<loaded_shaders.size(); subIndex++)
                {
                    if(shader_boundingBox_id == loaded_shaders[subIndex]->assetShaderId)
                        tempEntity->setShaderBoundingBox(loaded_shaders[subIndex]);
                }
            }
            
            tempEntity->setGeometry(loaded_geometry[0]);
            tempEntity->setName(name);
            tempEntity->setTag(tag);
            tempEntity->setType(type);
            tempEntity->setPosition(glm::vec3(xPos, yPos, zPos));
            tempEntity->setScale(glm::vec3(xScale, yScale, zScale));
            tempEntity->setRotation(glm::vec3( xRotation, yRotation, zRotation));
            tempEntity->setEnableRender(enableRender);
            tempEntity->setEnableBoundingBox(enableBoundingBox);
            tempEntity->setEnableCollider(enableCollider);
            tempEntity->setColor( glm::vec3( colorRed, colorGreen, colorBlue) );
            entities.push_back(tempEntity);
        }
    }
    return entities;
};