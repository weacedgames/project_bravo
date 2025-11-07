#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "entity.h"

#include "geometry.h"

#define PI 3.14159265358979323846f

class Graphics
{
private:
    unsigned int window_width;
    unsigned int window_height;
    glm::vec3 map_dimmensions;

    bool overlay_inititated = false;
    
public:
    GLFWwindow *window;
    


public:
    float deltaTime;
    float lastFrameTime;

public:
    Graphics(const int window_width,const int window_height, glm::vec3 mapDimmensions);

    int initiate();
    void test();
    void render(std::vector<Entity*> entitys, glm::mat4 projection, glm::mat4 view);

};

#endif