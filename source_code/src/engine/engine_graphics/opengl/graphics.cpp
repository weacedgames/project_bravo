#include "graphics.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
};


Graphics::Graphics(const int windowWidth,const int windowHeight, glm::vec3 mapDimmensions)
{
    window_width = windowWidth;
    window_height = windowHeight;
    map_dimmensions = mapDimmensions;
    deltaTime = 0.0f;
    lastFrameTime = 0.0f;

};


int Graphics::initiate()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, "BRAVO", NULL, NULL);
    glfwSetWindowPos(window, 100, 50); 
    
    if (window == NULL){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
    
    glClear(GL_DEPTH_BUFFER_BIT);

   
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    //glFrontFace(GL_CCW);

    return 1;
};

void Graphics::test()
{
    if(initiate()){
        Camera camera(window_width, window_height, glm::vec3(0.0f, 0.0f, 15.0f));
        Shader ourShader("./scene/assets/shaders/modelShader/modelShader.vert", "./scene/assets/shaders/modelShader/modelShader.frag", 0);
        Model modelHangar("./scene/assets/models/project_bravo_character/project_bravo_character.obj",0);
        
        float degrees = 180.0f;
        float pi = 3.14159265358979323846;

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)window_width / (float)window_height, 0.01f, 200.0f);
            glm::mat4 view = camera.getViewMatrix();
            glm::mat4 model = glm::mat4(1.0f);
            
            model = glm::translate(model, glm::vec3(0.0f));
            model = glm::scale(model, glm::vec3(5.0f));
            model = glm::rotate(model, degrees * ( pi/180) , glm::vec3(0.0f, 180.0f, 0.0f));
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

            ourShader.activate();
            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);
            ourShader.setMat4("model", model);
            
            modelHangar.draw(ourShader);
        
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwTerminate();
    }
};



void Graphics::render(std::vector<Entity*> entities, glm::mat4 projection, glm::mat4 view)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////
    // World Render
    ///////////////////////////////////////////////////////////////////////////////////////////

    for(int i=0; i<entities.size(); i++)
    {
        if(entities[i]->returnEnableRender() == true && entities[i]->returnType() == "model" || entities[i]->returnType() == "geometry" || entities[i]->returnType() == "collider")
        {
            Shader& entitiesShader = *entities[i]->returnShader();

            glm::vec3 converted_position = entities[i]->returnPosition() / map_dimmensions;
            glm::vec3 converted_scale = entities[i]->returnScale() / map_dimmensions;

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, converted_position);
            model = glm::rotate(model, entities[i]->returnRotation().x * ( PI/180) , glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, entities[i]->returnRotation().y * ( PI/180) , glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, entities[i]->returnRotation().z * ( PI/180) , glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, converted_scale);
            
            entities[i]->returnShader()->activate();
            entities[i]->returnShader()->setMat4("projection", projection);
            entities[i]->returnShader()->setMat4("view", view);
            entities[i]->returnShader()->setMat4("model", model);

            if(entities[i]->returnType() == "model")
            {
                entities[i]->returnModel()->draw(entitiesShader);
            }

            if(entities[i]->returnType() == "geometry")
            {
                    entities[i]->returnShader()->setVec3("color", entities[i]->returnColor() );
                    entities[i]->returnGeometry()->draw(entitiesShader);
            }

            if(entities[i]->returnType() == "collider")
            {
                    entities[i]->returnShader()->setVec3("color", entities[i]->returnColor() );
                    entities[i]->returnGeometry()->draw(entitiesShader);
            }

            //if(entities[i]->returnEnableBoundingBox() == true)
            //{
            //    Shader boundingBoxShader("./project/assets/shaders/boundingBoxShader/boundingBoxShader.vert", "./project/assets/shaders/boundingBoxShader/boundingBoxShader.frag");
            //    boundingBoxShader.activate();
            //    boundingBoxShader.setMat4("projection", projection);
            //    boundingBoxShader.setMat4("view", view);
            //    boundingBoxShader.setMat4("model", model);
            //    entities[i]->returnModel()->drawBoundingBox();
            //}

        }
    }



    ///////////////////////////////////////////////////////////////////////////////////////////
    // Overlay Models
    ///////////////////////////////////////////////////////////////////////////////////////////

    for(int i=0; i<entities.size(); i++)
    {
        if(entities[i]->returnEnableRender() == true && entities[i]->returnType() == "overlay")
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            Shader& entitiesShader = *entities[i]->returnShader();

            glm::mat4 fpsModel = glm::mat4(1.0f);
            fpsModel = glm::translate(fpsModel, entities[0]->returnPosition() / map_dimmensions);
            fpsModel = glm::rotate(fpsModel, glm::radians( entities[i]->returnRotation().x ) , glm::vec3(1.0f, 0.0f, 0.0f));
            fpsModel = glm::rotate(fpsModel, glm::radians( entities[i]->returnRotation().y ) , glm::vec3(0.0f, 1.0f, 0.0f));
            fpsModel = glm::rotate(fpsModel, glm::radians( entities[i]->returnRotation().z ) , glm::vec3(0.0f, 0.0f, 1.0f));
            fpsModel = glm::rotate(fpsModel, glm::radians( entities[i]->returnRotation().y - entities[0]->returnCamera()->camera_yaw ) , glm::vec3(0.0f, 1.0f, 0.0f));
            fpsModel = glm::rotate(fpsModel, glm::radians( entities[i]->returnRotation().x - entities[0]->returnCamera()->camera_pitch ) , glm::vec3(1.0f, 0.0f, 0.0f));
            fpsModel = glm::translate(fpsModel, glm::vec3(-7.0f, -5.0f, 20.0f) / map_dimmensions);
            fpsModel = glm::scale(fpsModel, entities[i]->returnScale() / map_dimmensions);

            entitiesShader.activate();
            entitiesShader.setMat4("projection", projection);
            entitiesShader.setMat4("view", view );
            entitiesShader.setMat4("model", fpsModel);

            entities[i]->returnModel()->draw(entitiesShader);       
        }  
    }


    ///////////////////////////////////////////////////////////////////////////////////////////
    // Overlay Sprites
    ///////////////////////////////////////////////////////////////////////////////////////////

    for(int i=0; i<entities.size(); i++)
    {
        if(entities[i]->returnEnableRender() == true && entities[i]->returnType() == "sprite")
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            Shader& entitieShader = *entities[i]->returnShader();

            glm::mat4 projection = glm::ortho(0.0f, (float)window_width, (float)window_height, 0.0f, -1.0f, 1.0f);
            
            glm::vec3 converted_position = entities[i]->returnPosition();
            glm::vec3 converted_scale = entities[i]->returnScale();

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, converted_position);
            model = glm::rotate(model, entities[i]->returnRotation().z * ( PI/180) , glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, converted_scale);

            entitieShader.activate();
            entitieShader.setMat4("projection", projection );
            entitieShader.setMat4("view",  glm::mat4(1.0f));
            entitieShader.setMat4("model", model);


            entities[i]->returnSprite()->draw(entitieShader);     
        }
    }


    glfwSwapBuffers(window);
    glfwPollEvents(); 
};