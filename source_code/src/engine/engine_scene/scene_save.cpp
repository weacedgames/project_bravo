#include "scene_save.h"

void SceneSave::save(std::vector<Entity*> entities)
{
    for(int i=0; i<entities.size(); i++)
    {
        std::string filename = "";
        std::string path = "./scene/temp_entities/";

        if(entities[i]->returnName() == "N/A" || entities[i]->returnName() == "")
            filename = "object_" + std::to_string(i) + ".entity";
        else
            filename = "object_" + std::to_string(i) + "_" + entities[i]->returnName() + ".entity";
            
        std::ofstream file_write(path + filename);

        if(file_write.is_open())
        {
            if(entities[i]->returnType() == "camera")
            {
                file_write << "TYPE=" << entities[i]->returnType() << std::endl;
                file_write << "NAME=" << entities[i]->returnName() << std::endl;
                file_write << "TAG=" << entities[i]->returnTag() << std::endl;

                file_write << "POSITIONX=" << entities[i]->returnPosition().x << std::endl;
                file_write << "POSITIONY=" << entities[i]->returnPosition().y << std::endl;
                file_write << "POSITIONZ=" << entities[i]->returnPosition().z << std::endl;

                file_write << "ROTATIONX=" << entities[i]->returnRotation().x << std::endl;
                file_write << "ROTATIONY=" << entities[i]->returnRotation().y << std::endl;
                file_write << "ROTATIONZ=" << entities[i]->returnRotation().z << std::endl;
            }

            if(entities[i]->returnType() == "model")
            {
                file_write << "TYPE=" << entities[i]->returnType() << std::endl;
                file_write << "NAME=" << entities[i]->returnName() << std::endl;
                file_write << "TAG=" << entities[i]->returnTag() << std::endl;
                
                file_write << "SHADERID=" << entities[i]->returnShader()->assetShaderId << std::endl;
                file_write << "SHADERBOUNDINGBOXID=0" << std::endl;
                file_write << "MODELID=" << entities[i]->returnModel()->assetModelID << std::endl;

                file_write << "POSITIONX=" << entities[i]->returnPosition().x << std::endl;
                file_write << "POSITIONY=" << entities[i]->returnPosition().y << std::endl;
                file_write << "POSITIONZ=" << entities[i]->returnPosition().z << std::endl;

                file_write << "SCALEX=" << entities[i]->returnScale().x << std::endl;
                file_write << "SCALEY=" << entities[i]->returnScale().y << std::endl;
                file_write << "SCALEZ=" << entities[i]->returnScale().z << std::endl;
                
                file_write << "ROTATIONX=" << entities[i]->returnRotation().x << std::endl;
                file_write << "ROTATIONY=" << entities[i]->returnRotation().y << std::endl;
                file_write << "ROTATIONZ=" << entities[i]->returnRotation().z << std::endl;

                file_write << "ENABLERENDER=" << entities[i]->returnEnableRender() << std::endl;
                file_write << "ENABLEBOUNDINGBOX=" << entities[i]->returnEnableBoundingBox() << std::endl;
            }

            if(entities[i]->returnType() == "geometry")
            {
                file_write << "TYPE=" << entities[i]->returnType() << std::endl;
                file_write << "NAME=" << entities[i]->returnName() << std::endl;
                file_write << "TAG=" << entities[i]->returnTag() << std::endl;

                file_write << "SHADERID=" << entities[i]->returnShader()->assetShaderId << std::endl;
                file_write << "SHADERBOUNDINGBOXID=0" << std::endl;
                file_write << "GEOMETRYTYPE=" << entities[i]->returnGeometry()->returnGeometryType() << std::endl;
                file_write << "GEOMETRYCOLORRED=" << entities[i]->returnColor().x << std::endl;
                file_write << "GEOMETRYCOLORGREEN=" << entities[i]->returnColor().y << std::endl;
                file_write << "GEOMETRYCOLORBLUE=" << entities[i]->returnColor().z << std::endl;
                
                file_write << "POSITIONX=" << entities[i]->returnPosition().x << std::endl;
                file_write << "POSITIONY=" << entities[i]->returnPosition().y << std::endl;
                file_write << "POSITIONZ=" << entities[i]->returnPosition().z << std::endl;

                file_write << "SCALEX=" << entities[i]->returnScale().x << std::endl;
                file_write << "SCALEY=" << entities[i]->returnScale().y << std::endl;
                file_write << "SCALEZ=" << entities[i]->returnScale().z << std::endl;

                file_write << "ROTATIONX=" << entities[i]->returnRotation().x << std::endl;
                file_write << "ROTATIONY=" << entities[i]->returnRotation().y << std::endl;
                file_write << "ROTATIONZ=" << entities[i]->returnRotation().z << std::endl;

                file_write << "ENABLERENDER=" << entities[i]->returnEnableRender() << std::endl;
                file_write << "ENABLEBOUNDINGBOX=" << entities[i]->returnEnableBoundingBox() << std::endl;
                file_write << "ENABLECOLLIDER=1" << std::endl;

            }

            if(entities[i]->returnType() == "overlay")
            {
                file_write << "TYPE=" << entities[i]->returnType() << std::endl;
                file_write << "NAME=" << entities[i]->returnName() << std::endl;
                file_write << "TAG=" << entities[i]->returnName() << std::endl;
                
                file_write << "SHADERID=" << entities[i]->returnShader()->assetShaderId << std::endl;
                file_write << "SHADERBOUNDINGBOXID=0" << std::endl;
                file_write << "MODELID=" << entities[i]->returnModel()->assetModelID << std::endl;
                
                file_write << "POSITIONX=" << entities[i]->returnPosition().x << std::endl;
                file_write << "POSITIONY=" << entities[i]->returnPosition().y << std::endl;
                file_write << "POSITIONZ=" << entities[i]->returnPosition().z << std::endl;

                file_write << "SCALEX=" << entities[i]->returnScale().x << std::endl;
                file_write << "SCALEY=" << entities[i]->returnScale().y << std::endl;
                file_write << "SCALEZ=" << entities[i]->returnScale().z << std::endl;
                
                file_write << "ROTATIONX=" << entities[i]->returnRotation().x << std::endl;
                file_write << "ROTATIONY=" << entities[i]->returnRotation().y << std::endl;
                file_write << "ROTATIONZ=" << entities[i]->returnRotation().z << std::endl;

                file_write << "ENABLERENDER=" << entities[i]->returnEnableRender() << std::endl;
                file_write << "ENABLEBOUNDINGBOX=" << entities[i]->returnEnableBoundingBox() << std::endl;
            }

            file_write.close();
        }
        else
        {
            std::cerr << "ERROR::SAVING_GAMEOBJECTS" << std::endl;
        }
    }
};
