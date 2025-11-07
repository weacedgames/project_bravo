#include "model.h"

Model::Model(std::string const &path, int setId)
{

    modelPath = path;
    id = setId;
    loadModel(path);

    create_boundingBox();
};

void Model::loadModel(std::string const &path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
};


void Model::draw(Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
};

void Model::create_boundingBox()
{
    boundingBoxIndices = {
        0, 1, 2,
        2, 3, 1,
        4, 5, 6,
        6, 7, 5,
        0, 1, 4,
        4, 5, 1,
        2, 3, 6,
        6, 7, 3,
        0, 2, 4,
        4, 6, 2,
        1, 3, 5,
        5, 7, 3
    };

    std::vector<glm::vec3> positions = {
        //Bottom
        glm::vec3(x_min, y_min, z_max),
        glm::vec3(x_max, y_min, z_max),
        glm::vec3(x_min, y_min, z_min),
        glm::vec3(x_max, y_min, z_min),
        
        // Top
        glm::vec3(x_min, y_max, z_max),
        glm::vec3(x_max, y_max, z_max),
        glm::vec3(x_min, y_max, z_min),
        glm::vec3(x_max, y_max, z_min)
    };

    for(int i=0; i<positions.size(); i++){
        glm::vec3 vector;
        vector.x = positions[i].x;
        vector.y = positions[i].y;
        vector.z = positions[i].z;

        Vertex vertex;
        vertex.Position = vector;

        boundingBox.push_back(vertex);
    }
};

void Model::drawBoundingBox()
{
    GLuint VAO, EBO, VBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    
    glBufferData(GL_ARRAY_BUFFER,this->boundingBox.size() * sizeof(Vertex),&this->boundingBox[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,this->boundingBoxIndices.size() * sizeof(unsigned int),&this->boundingBoxIndices[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);

    glBindVertexArray(VAO);
    glLineWidth(5.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, this->boundingBoxIndices.size(), GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
    glBindVertexArray(0);
};

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));			
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
};


Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        // Bounding Box
        if(std::isnan(x_min)){
            x_min = mesh->mVertices[i].x;
        }else{
            if(x_min > mesh->mVertices[i].x)
                x_min = mesh->mVertices[i].x;
        }

        if(std::isnan(x_max)){
            x_max = mesh->mVertices[i].x;
        }else{
            if(x_max < mesh->mVertices[i].x)
                x_max = mesh->mVertices[i].x;
        }

        if(std::isnan(y_min)){
            y_min = mesh->mVertices[i].y;
        }else{
            if(y_min > mesh->mVertices[i].y)
                y_min = mesh->mVertices[i].y;
        }

        if(std::isnan(y_max)){
            y_max = mesh->mVertices[i].y;
        }else{
            if(y_max < mesh->mVertices[i].y)
                y_max = mesh->mVertices[i].y;
        }

        if(std::isnan(z_min)){
            z_min = mesh->mVertices[i].z;
        }else{
            if(z_min > mesh->mVertices[i].z)
                z_min = mesh->mVertices[i].z;
        }

        if(std::isnan(z_max)){
            z_max = mesh->mVertices[i].z;
        }else{
            if(z_max < mesh->mVertices[i].z)
                z_max = mesh->mVertices[i].z;
        }
        // End Bounding Box

        // Model
        Vertex vertex;
        glm::vec3 vector;
        
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if(mesh->mTextureCoords[0]) 
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;

            // !!! Crashes best guess if tanget is not present and needs to be accounted for, basically check if data is present in the model
            // tangent
            //vector.x = mesh->mTangents[i].x;
            //vector.y = mesh->mTangents[i].y;
            //vector.z = mesh->mTangents[i].z;
            //vertex.Tangent = vector;


            // bitangent
            //vector.x = mesh->mBitangents[i].x;
            //vector.y = mesh->mBitangents[i].y;
            //vector.z = mesh->mBitangents[i].z;
            //vertex.Bitangent = vector;
        }else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }

    // Indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }


    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    

    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh(vertices, indices, textures);
};

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++){
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0){
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip){   
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
};

unsigned int Model::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
};

std::string Model::returnModelPath()
{
    return modelPath;
};

std::vector<Vertex> Model::returnBoundingBox()
{
    return this->boundingBox;
};