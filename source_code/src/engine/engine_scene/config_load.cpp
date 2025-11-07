#include "config_load.h"

std::vector<Model*> ConfigLoad::loadModels()
{
    std::vector<Model*> loaded_models;

    std::vector<std::vector<std::string>> files;

    for (const auto& entry : std::filesystem::directory_iterator("./scene/config/model"))
    {
        std::vector<std::string> file;
        
        std::ifstream file_read("./scene/config/model/" + entry.path().filename().string());
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
            std::cerr << "ERROR::LOADING_CONFIG" << std::endl;
        }
        files.push_back(file);
    }

    for(int index=0; index < files.size() ; index++)
    {
        std::string id = "";
        std::string name = "";
        std::string directoryRoot = "";
        std::string directory = "";
        std::string fileName = "";
        std::string fileType = "";


        for(int subIndex=0; subIndex<files[index].size(); subIndex++)
        {
            size_t pos = files[index][subIndex].find('=');

            if(pos != std::string::npos)
            {
                std::string key = files[index][subIndex].substr(0, pos);
                std::string value = files[index][subIndex].substr(pos + 1);

                if(key=="MODELID")
                    id = value;
                if(key=="DIRECTORYROOT")
                    directoryRoot = value;
                if(key=="DIRECTORY")
                    directory = value;
                if(key=="FILENAME")
                    fileName = value;
                if(key=="FILETYPE")
                    fileType = value;
            }
        }

        loaded_models.push_back(new Model(directoryRoot + directory + fileName, std::stoi(id)));
    }

    return loaded_models;
};


//std::vector<Sprite*> ConfigLoad::loadSprites()
//{
//    std::vector<Sprite*> loaded_sprites;
//
//    std::vector<std::vector<std::string>> files;
//
//    for (const auto& entry : std::filesystem::directory_iterator("./scene/config/sprites"))
//    {
//        std::vector<std::string> file;
//        
//        std::ifstream file_read("./scene/config/sprites/" + entry.path().filename().string());
//        if(file_read.is_open())
//        {
//            std::string line;
//            while(getline(file_read, line)){
//                file.push_back(line);
//            }
//            file_read.close();
//        }
//        else
//        {
//            std::cerr << "ERROR::LOADING_CONFIG" << std::endl;
//        }
//        files.push_back(file);
//    }
//
//    for(int index=0; index < files.size() ; index++)
//    {
//        std::string id = "";
//        std::string name = "";
//        std::string directoryRoot = "";
//        std::string directory = "";
//        std::string fileName = "";
//        std::string fileType = "";
//
//
//        for(int subIndex=0; subIndex<files[index].size(); subIndex++)
//        {
//            size_t pos = files[index][subIndex].find('=');
//
//            if(pos != std::string::npos)
//            {
//                std::string key = files[index][subIndex].substr(0, pos);
//                std::string value = files[index][subIndex].substr(pos + 1);
//
//                if(key=="SPRITEID")
//                    id = value;
//                if(key=="DIRECTORYROOT")
//                    directoryRoot = value;
//                if(key=="DIRECTORY")
//                    directory = value;
//                if(key=="FILENAME")
//                    fileName = value;
//                if(key=="FILETYPE")
//                    fileType = value;
//            }
//        }
//
//        // I dont like declaring the Size Here , just want the data
//        // Thats why no size here just bs
//
//        loaded_sprites.push_back(new Sprite(directoryRoot + directory + fileName, 900, 450, std::stoi(id)));
//    }
//
//    return loaded_sprites;
//};



std::vector<Sprite*> ConfigLoad::loadSprites()
{
    std::vector<Sprite*> loaded_sprites;

    std::vector<std::vector<std::string>> files;

    for (const auto& entry : std::filesystem::directory_iterator("./scene/config/sprites"))
    {
        std::vector<std::string> file;
        
        std::ifstream file_read("./scene/config/sprites/" + entry.path().filename().string());
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
            std::cerr << "ERROR::LOADING_CONFIG" << std::endl;
        }
        files.push_back(file);
    }

    for(int index=0; index < files.size() ; index++)
    {
        std::string id = "";
        std::string name = "";
        std::string directoryRoot = "";
        std::string directory = "";
        std::string fileName = "";
        std::string fileType = "";


        for(int subIndex=0; subIndex<files[index].size(); subIndex++)
        {
            size_t pos = files[index][subIndex].find('=');

            if(pos != std::string::npos)
            {
                std::string key = files[index][subIndex].substr(0, pos);
                std::string value = files[index][subIndex].substr(pos + 1);

                if(key=="SPRITEID")
                    id = value;
                if(key=="DIRECTORYROOT")
                    directoryRoot = value;
                if(key=="DIRECTORY")
                    directory = value;
                if(key=="FILENAME")
                    fileName = value;
                if(key=="FILETYPE")
                    fileType = value;
            }
        }

        loaded_sprites.push_back(new Sprite( 0.0f, 0.0f, 1800.0f, 900.0f, directoryRoot + directory + fileName, std::stoi(id)));
    }
    return loaded_sprites;
};

std::vector<Shader*> ConfigLoad::loadShaders()
{
    std::vector<Shader*> loaded_shaders;

    std::vector<std::vector<std::string>> files;

    for (const auto& entry : std::filesystem::directory_iterator("./scene/config/shaders"))
    {
        std::vector<std::string> file;
        
        std::ifstream file_read("./scene/config/shaders/" + entry.path().filename().string());
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
            std::cerr << "ERROR::LOADING_CONFIG" << std::endl;
        }
        files.push_back(file);
    }

    for(int index=0; index < files.size() ; index++)
    {
        std::string id = "";
        std::string name = "";

        std::string directoryRoot = "";
        std::string directory = "";

        std::string fileNameVertex = "";
        std::string fileNameFragment = "";

        for(int subIndex=0; subIndex<files[index].size(); subIndex++)
        {
            size_t pos = files[index][subIndex].find('=');

            if(pos != std::string::npos)
            {
                std::string key = files[index][subIndex].substr(0, pos);
                std::string value = files[index][subIndex].substr(pos + 1);

                if(key=="SHADERID")
                    id = value;
                if(key=="DIRECTORYROOT")
                    directoryRoot = value;
                if(key=="DIRECTORY")
                    directory = value;
                if(key=="FILENAMEVERTEX")
                    fileNameVertex = value;
                if(key=="FILENAMEFRAGMENT")
                    fileNameFragment = value;
            }
        }

        loaded_shaders.push_back( new Shader((directoryRoot + directory + fileNameVertex).c_str(), (directoryRoot + directory + fileNameFragment).c_str(), std::stoi(id)) );
    }

    return loaded_shaders;
};