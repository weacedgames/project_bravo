#include "Sprite.h"

Sprite::Sprite(float width, float height, std::string const &texture_filePath, int setSpriteID)
{
    assetSpriteID = setSpriteID;
    
    /////////////////////////////////
    // Step 1: Create Sprite Image Face
    /////////////////////////////////

    float vertices[] = 
    {
        // Positions   // Sprite Coordinates
        (-(width/2)/1000)  , ( (height/2)/1000) , 0.0f, 0.0f, 1.0f,
        ( (width/2)/1000)  , ( (height/2)/1000) , 0.0f, 1.0f, 1.0f,
        ( (width/2)/1000)  , (-(height/2)/1000)   , 0.0f, 1.0f, 0.0f,
        (-(width/2)/1000)  , (-(height/2)/1000)   , 0.0f, 0.0f, 0.0f

    };



    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    /////////////////////////////////
    // Step 2: Load Sprite Image
    /////////////////////////////////


    glGenTextures( 1, &SpriteImage);
    glBindTexture( GL_TEXTURE_2D, SpriteImage);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    int image_width;
    int image_height;
    int nrChannels;
    unsigned char* data;


    stbi_set_flip_vertically_on_load(true);
    
    data = stbi_load( texture_filePath.c_str(), &image_width, &image_height, &nrChannels, 0);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR::IMAGE:Failed_TO_LOAD\n" << std::endl;
    }

    stbi_image_free(data);
};

void Sprite::draw(Shader &shader)
{   
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SpriteImage);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

};