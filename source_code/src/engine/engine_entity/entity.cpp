////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | //
//                      ---WEACEDGAMES PERSONNEL---                       //
//                                                                        //
//                                                                        //
// SUMMARY METADATA:                                                      //
// -> Company: WeAcEd GaMeS                                               //
// -> Author First Name: The                                              //
// -> Author First Name: Programmer                                       //
// -> Version: version.alpha.1.0                                          //
// -> File: entity.cpp                                                    //
// -> Date Created: 07-25-2026                                            //
// -> Date Updated: 07-25-2026                                            //
//                                                                        //
// SUMMARY DESCRIPTION:                                                   //
// -> This is a class based entity system. Fat and Bulky but simple as    //
// hell.                                                                  //
//                                                                        //
// SUMARRY NOTES:                                                         //
// -> This is currently a class based entity system. I would like to      //
// eventually have a Entity Component System also, one for effieceny      //
// the other for simplicty.                                               //
//                                                                        //
//                                                                        //
//                      ---WEACEDGAMES PERSONNEL---                       //
//  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | //
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

#include "entity.h"

Entity::Entity()
{
    finalBones.assign(100, glm::mat4(1.0f));
};

void Entity::setCamera(Camera* handleCamera){entity_camera = handleCamera;};
void Entity::setShader(Shader* handleShader){entity_shader = handleShader;};
void Entity::setShaderBoundingBox(Shader* handleShaderBB){entity_shader = handleShaderBB;};
void Entity::setModel(Model* handleModel){entity_model = handleModel;};
void Entity::setSprite(Sprite* handleSprite){entity_sprite =  handleSprite;};
void Entity::setGeometry(Geometry* handleGeometry){entity_geometry = handleGeometry;};

void Entity::setType(std::string type){entity_type = type;};
void Entity::setID(int id){entity_id = id;};
void Entity::setName(std::string name){entity_name = name;};
void Entity::setTag(std::string tag){entity_tag = tag;};

void Entity::setPosition(glm::vec3 position){entity_position = position;};
void Entity::setScale(glm::vec3 scale){entity_scale = scale;};
void Entity::setRotation(glm::vec3 rotation){entity_rotation = rotation;};

void Entity::setVelocity(glm::vec3 velocity){entity_velocity = velocity;};
void Entity::setColor(glm::vec3 setColor){entity_color = setColor;};

void Entity::setEnableRender(bool enable){enableRender = enable;};
void Entity::setEnableBoundingBox(bool enable){enableBoundingBox = enable;};
void Entity::setEnableCollider(bool enable){enableCollider = enable;};

///////////////////////////////////////////////////////////////////////////////////////

Camera* Entity::returnCamera(){return entity_camera;};
Shader* Entity::returnShader(){return entity_shader;};
Shader* Entity::returnShaderBoundingBox(){return entity_shader_boundingBox;};
Model* Entity::returnModel(){return entity_model;};
Sprite* Entity::returnSprite(){return entity_sprite;};
Geometry* Entity::returnGeometry(){return entity_geometry;};

std::string Entity::returnType(){return entity_type;};
int Entity::returnID(){return entity_id;};
std::string Entity::returnName(){return entity_name;};
std::string Entity::returnTag(){return entity_tag;};

glm::vec3 Entity::returnPosition(){return entity_position;};
glm::vec3 Entity::returnScale(){return entity_scale;};
glm::vec3 Entity::returnRotation(){return entity_rotation;};

glm::vec3 Entity::returnVelocity(){return entity_velocity;};
glm::vec3 Entity::returnColor(){return entity_color;};

bool Entity::returnEnableRender(){return enableRender;};
bool Entity::returnEnableBoundingBox(){return enableBoundingBox;};
bool Entity::returnEnableCollider(){return enableCollider;};
