#ifndef GAME_H
#define GAME_H


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>

#include <Windows.h>
#include <mmsystem.h>

#include "camera.h"
#include "shader.h"
#include "model.h"
#include "graphics.h"
#include "entity.h"
#include "rigid_body.h"
#include "collider.h"
#include "collision.h"
#include "geometry.h"
#include "scene_save.h"
#include "scene_load.h"
#include "network_server.h"
#include "network_client.h"
#include "keyboard.h"
#include "mouse.h"
#include "raycast.h"
#include "config_load.h"
#include "audio.h"
#include "audio_file.h"

#include "sprite.h"


#pragma comment(lib, "winmm.lib")

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 900

#define MAP_WIDTH 1000.0f
#define MAP_HEIGHT 1000.0f
#define MAP_DEPTH 1000.0f


class Game
{
private:
    std::vector<Shader*> loaded_shaders;
    std::vector<Model*> loaded_models;
    std::vector<Sprite*> loaded_sprites;
    std::vector<Geometry*> loaded_geometry;
    std::vector<Entity*> loaded_entities;


private:
    glm::vec3 map_dimmensions = glm::vec3(MAP_WIDTH, MAP_HEIGHT, MAP_DEPTH);

    Graphics graphics;
    Camera camera;
    Keyboard keyboard;
    Mouse mouse;

    bool mouseLeftClick = true;
    float lastX = WINDOW_WIDTH / 2.0f;
    float lastY = WINDOW_HEIGHT/ 2.0f;

private:
    void initiate();
    void mainloop();

    void processInputKeyboard(GLFWwindow *window, Entity *entity);
    void processInputMouse();


public:
    Game();
    ~Game();
    void play();

};

#endif