#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CAMERA_MOVEMENT
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
private:
    int window_width;
    int window_height;

private:
    glm::vec3 camera_position = glm::vec3( 0.0f, 0.0f, 0.0f);

public:
    
    glm::vec3 camera_front = glm::vec3( 0.0f, 0.0f, -1.0f);
    glm::vec3 camera_up = glm::vec3( 0.0f, 1.0f, 0.0f); 

    float camera_yaw = -90.0f;
    float camera_pitch = 0.0f;
    float camera_fov = 45.0f;

public:
    Camera( int screenWidth, int screenHeight, glm::vec3 position);
    glm::mat4 getViewMatrix();
    void processKeyboardInput( CAMERA_MOVEMENT direction, float deltaTime);
    void processMouseInput( float xoffset, float yoffset);
    void processMouseScroll(float yoffset);

public:
    void setCameraPosition(glm::vec3 setPosition);

public:
    glm::vec3 returnCameraPosition();
    
};

#endif