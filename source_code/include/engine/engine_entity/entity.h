#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "model.h"
#include "camera.h"
#include "geometry.h"
#include "Sprite.h"

class Entity
{

private:
    Camera* entity_camera;
    Shader* entity_shader;
    Model* entity_model;
    Sprite* entity_sprite;
    Geometry* entity_geometry;

    int entity_id;
    std::string entity_type;
    std::string entity_name;
    std::string entity_tag;
    glm::vec3 entity_position;
    glm::vec3 entity_scale;
    glm::vec3 entity_rotation;
    glm::vec3 entity_velocity;

    glm::vec3 entity_color;

    bool enableRender;
    bool enableBoundingBox;
    bool enableCollider;

public:
    void setCamera(Camera* handleCamera);
    void setShader(Shader* handleShader);
    void setModel(Model* handleModel);
    void setSprite(Sprite* handleSprite);
    void setGeometry(Geometry* handleGeometry);

    void setID(int id);
    void setType(std::string type);
    void setName(std::string name);
    void setTag(std::string tag);
    void setPosition(glm::vec3 position);
    void setScale(glm::vec3 scale);
    void setRotation(glm::vec3 rotation);
    void setVelocity(glm::vec3 velocity);
    void setColor(glm::vec3 setColor);
    
    void setEnableRender(bool enable);
    void setEnableBoundingBox(bool enable);
    void setEnableCollider(bool enable);

public:
    Camera* returnCamera();
    Shader* returnShader();
    Model* returnModel();
    Sprite* returnSprite();
    Geometry* returnGeometry();
    
    int returnID();
    std::string returnType();
    std::string returnName();
    std::string returnTag();
    glm::vec3 returnPosition();
    glm::vec3 returnScale();
    glm::vec3 returnRotation();
    glm::vec3 returnVelocity();
    glm::vec3 returnColor();

    bool returnEnableRender();
    bool returnEnableBoundingBox();
    bool returnEnableCollider();
};

#endif