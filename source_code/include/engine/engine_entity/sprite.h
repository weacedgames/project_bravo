#ifndef Sprite_H
#define Sprite_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include <string>
#include "shader.h"
#include "image.h"

class Sprite
{
private:
    unsigned int VAO, VBO, EBO;
    unsigned int SpriteImage;
    
public:
    int assetSpriteID;

    Sprite( float width, float height, std::string const &texture_filePath, int setSpriteID);

    void draw(Shader &shader);
};

#endif