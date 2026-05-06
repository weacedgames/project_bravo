#include "game.h"

struct EntityClass
{
    std::string className;
    std::vector<Entity*> entities;
};


Game::Game(): graphics(WINDOW_WIDTH, WINDOW_HEIGHT, map_dimmensions), camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f)), keyboard(&graphics), mouse(&graphics, WINDOW_WIDTH, WINDOW_HEIGHT)
{
    if(graphics.initiate())
    {
        glfwSetWindowUserPointer(graphics.window, this);
        glfwSetCursorPosCallback(graphics.window, mouse.mouse_callback);
        glfwSetScrollCallback(graphics.window, mouse.scroll_callback);

        initiate();
    }
};


void Game::initiate()
{
    // Loading Assets
    ConfigLoad configLoad;
    loaded_models = configLoad.loadModels();
    loaded_shaders = configLoad.loadShaders();
    loaded_sprites = configLoad.loadSprites();
    loaded_geometry.push_back(new Geometry(0)); 

    std::cout << "Loading Assets Completed" << std::endl;

    // Building Scene
    SceneLoad sceneLoad;
    std::vector<std::vector<std::string>> files = sceneLoad.loadEntities();

    loaded_entities = sceneLoad.generateEntities(files, loaded_shaders, loaded_models, loaded_sprites, loaded_geometry, &camera);

    std::cout << "Scene Loading Complete" << std::endl;

    // Load Cameras
    for(size_t i=0;i<loaded_entities.size();i++) if(loaded_entities[i]->returnType()=="camera") loaded_cameras.push_back(loaded_entities[i]);


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // WORK IN PROGRESS
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Thoughts

    // Duplicate Class
    // Duplicate needed entities
    // Assign it a id to be referenced
    // I dont like classes or sub classes to be the id because its soul job is categorize and template
    // I dont like using tag because thats not it intent
    // A class ID is needed I think

    // 0  = Template
    // 1+ =  Is Copy or duplicate
    // 2  = Means there are 3x copies present

    // CLASS  ID is a food for thought to add to file
    // Entity ID is meant for each Entity

    // THIS IS A SKETCH
    // Not sure yet
    // Generate Classes

    // std::vector<EntityClass> classes;
    // for(size_t i=0;i<loaded_entities.size();i++) 
    // {
    //     for(size_t j=0;j<classes.size(); j++)
    //     {
    //         if(loaded_entities[i]->returnClass()!=classes[j].className)
    //         {
    //             EntityClass entityClass;
    //             entityClass.className = loaded_entities[i]->returnName();
    //             entityClass.entities.push_back(loaded_entities[i]);
    //             classes.push_back(entityClass);
    //         }
    //         else
    //         {
    //             classes[j].entities.push_back(loaded_entities[i]);
    //         }
    //     }
    // }


    // TO DO:
    // Finish Animation
    // Mesh needs to also contain bone data so it also can be passed to the shader
    // 

    // THINKING.... 12:54 AM

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // WORK IN PROGRESS
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // I want to put this thread inside the class
    // Loading Audio    
    AudioFile audioFile_1("./scene/assets/audio/stonemans_melody_rave.wav", 0);
    AudioFile audioFile_2("./scene/assets/audio/stonemans_melody_8bit_exploration.wav", 1);
    AudioFile audioFile_3("./scene/assets/audio/sfx_laser.wav", 2);
    std::thread([audioFile_1, audioFile_2]
    {
        CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        Audio audio(audioFile_1.audioData, audioFile_2.audioData);
        audio.start();
        CoUninitialize();
    }).detach();    

};

Game::~Game()
{
    for(int i=0; i<loaded_entities.size(); i++)
        delete loaded_entities[i];
    glfwTerminate();
};

void Game::play()
{
    mainloop();
};

void Game::mainloop()
{
    ///////////////////////////////////////////////////////
    // Gameplan
    //////////////////////////////////////////////////////
    //  
    //  
    //  Player 1 (Server)
    //  Player 2 (Client)
    //  
    //  
    //////////////////////////////////////////////////////
    //////////////////////////////////////////////////////

    // I dont like the hard coding of this. Will need to create a elegant solution for networking.

    int selectPlayer = 1;

    NetworkServerUDP* networkServer = nullptr;

    if(selectPlayer==1)
    {
        networkServer = new NetworkServerUDP;
    }

    NetworkClientUDP networkClient(selectPlayer);

    while (!glfwWindowShouldClose(graphics.window))
    {
        ///////////////////////////////////////
        // Frame Speed
        ///////////////////////////////////////

        float currentFrameTime = glfwGetTime();
        graphics.deltaTime = currentFrameTime - graphics.lastFrameTime; 
        graphics.lastFrameTime = currentFrameTime;

        ///////////////////////////////////////
        // Input
        ///////////////////////////////////////

        if(selectPlayer == 1)
        {
            if (keyboard.inputKeyboard() == 130) // W
                networkClient.player_1_action = 1;
            if (keyboard.inputKeyboard() == 144) // S
                networkClient.player_1_action = 2;
            if (keyboard.inputKeyboard() == 143) // A
                networkClient.player_1_action = 3;
            if (keyboard.inputKeyboard() == 145) // D
                networkClient.player_1_action = 4;

            if (keyboard.inputKeyboard() == 169) // Space
                networkClient.player_1_action = 5;
            if (keyboard.inputKeyboard() == 167) // Alt
                networkClient.player_1_action = 6;
        }

        if(selectPlayer == 2)
        {
            if (keyboard.inputKeyboard() == 130) // W
                networkClient.player_2_action = 1;
            if (keyboard.inputKeyboard() == 144) // S
                networkClient.player_2_action = 2;
            if (keyboard.inputKeyboard() == 143) // A
                networkClient.player_2_action = 3;
            if (keyboard.inputKeyboard() == 145) // D
                networkClient.player_2_action = 4;

            if (keyboard.inputKeyboard() == 169) // Space
                networkClient.player_2_action = 5;
            if (keyboard.inputKeyboard() == 167) // Alt
                networkClient.player_2_action = 6;
        }

        processInputKeyboard(graphics.window, loaded_cameras[0]);
        processInputMouse();
        
        ///////////////////////////////////////
        // Camera
        ///////////////////////////////////////

        camera.setCameraPosition(loaded_cameras[0]->returnPosition() / map_dimmensions);
        glm::mat4 projection = glm::perspective(glm::radians(camera.camera_fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 150.0f);
        glm::mat4 view = camera.getViewMatrix();

        ///////////////////////////////////////
        // Logic
        ///////////////////////////////////////
        


        ///////////////////////////////////////
        // Render
        ///////////////////////////////////////
        
        graphics.render(graphics.deltaTime, loaded_entities, projection, view);
    }
};


void Game::processInputKeyboard(GLFWwindow *window, Entity *entity)
{
    const float speed = 2.0f;
    const float climbSpeed = 3.0f;

    if (keyboard.inputKeyboard() == 130)
        entity->setPosition( glm::vec3( entity->returnPosition().x + (speed * camera.camera_front.x), entity->returnPosition().y + (speed * camera.camera_front.y), entity->returnPosition().z + (speed * camera.camera_front.z) ) );
    if (keyboard.inputKeyboard() == 144)
        entity->setPosition(glm::vec3( entity->returnPosition().x - (speed * camera.camera_front.x), entity->returnPosition().y - (speed * camera.camera_front.y), entity->returnPosition().z - (speed * camera.camera_front.z) ) );
    if (keyboard.inputKeyboard() == 143)
        entity->setPosition(entity->returnPosition() - (speed * glm::normalize(glm::cross(camera.camera_front, camera.camera_up))) );
    if (keyboard.inputKeyboard() == 145)
        entity->setPosition(entity->returnPosition() + (speed * glm::normalize(glm::cross(camera.camera_front, camera.camera_up))) );
    if (keyboard.inputKeyboard() == 169)
        entity->setPosition(glm::vec3( entity->returnPosition().x, entity->returnPosition().y + climbSpeed , entity->returnPosition().z));
    if (keyboard.inputKeyboard() == 167)
        entity->setPosition(glm::vec3( entity->returnPosition().x, entity->returnPosition().y - climbSpeed , entity->returnPosition().z));
    if (keyboard.inputKeyboard() == 101)
        glfwSetWindowShouldClose(window, true);
};

void Game::processInputMouse()
{
    if(Mouse::cursor_active)
    {
        camera.processMouseInput(Mouse::cursor_xPos, Mouse::cursor_yPos);
        Mouse::cursor_active = false;
    }
    if(Mouse::scroll_active)
    {
        camera.processMouseScroll(float(Mouse::scroll_yPos));
        Mouse::scroll_active = false;
    }
}