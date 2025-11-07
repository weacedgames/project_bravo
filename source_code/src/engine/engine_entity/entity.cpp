#include "entity.h"


void Entity::setCamera(Camera* handleCamera){entity_camera = handleCamera;};
void Entity::setShader(Shader* handleShader){entity_shader = handleShader;};
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
Model* Entity::returnModel(){return entity_model;};
Sprite* Entity::returnSprite(){return entity_sprite;};
Geometry* Entity::returnGeometry(){return entity_geometry;};

int Entity::returnID(){return entity_id;};
std::string Entity::returnType(){return entity_type;};
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