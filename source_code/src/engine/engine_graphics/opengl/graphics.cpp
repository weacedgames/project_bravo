////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | //
//                      ---WEACEDGAMES PERSONNEL---                       //
//                                                                        //
//                                                                        //
// SUMMARY METADATA:                                                      //
// -> Company: WeAcEd GaMeS                                               //
// -> Author First Name: The                                              //
// -> Author Last Name: Programmer                                        //
// -> Version: version.alpha.1.0                                          //
// -> File: graphics.cpp                                                  //
// -> Date Created: 07-25-2026                                            //
// -> Date Updated: 07-25-2026                                            //
//                                                                        //
// SUMMARY DESCRIPTION:                                                   //
// -> This where the entities a rendered. Entity data is sent from        //
// game class. Entities with Enable Render set true are rendered.         //
//                                                                        //
// SUMARRY NOTES:                                                         //
// -> Animation needs to be completed. Still trying to figure that        //
// shit out.                                                              //
//                                                                        //
//                                                                        //
//                      ---WEACEDGAMES PERSONNEL---                       //
//  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | //
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

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

















void Graphics::render(float deltaTime, std::vector<Entity*> entities, glm::mat4 projection, glm::mat4 view)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    ///////////////////////////////////////////////////////////////////////////////////////////
    // START World Render
    ///////////////////////////////////////////////////////////////////////////////////////////

    for(int i=0; i<entities.size(); i++)
    {


        //////////////////////////////////////////
        // Model
        //////////////////////////////////////////

        if(entities[i]->returnType() == "model" && entities[i]->returnEnableRender() == true)
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
            
            entitiesShader.activate();
            entitiesShader.setMat4("projection", projection);
            entitiesShader.setMat4("view", view);
            entitiesShader.setMat4("model", model);

            animation(entities[i], entitiesShader);

            entities[i]->returnModel()->draw(entitiesShader);
            
            if(entities[i]->returnEnableBoundingBox() == true)
            {
                Shader& boundingBoxShader = *entities[i]->returnShaderBoundingBox();
                boundingBoxShader.activate();
                boundingBoxShader.setMat4("projection", projection);
                boundingBoxShader.setMat4("view", view);
                boundingBoxShader.setMat4("model", model);
                entities[i]->returnModel()->drawBoundingBox();
            }
        }








        //////////////////////////////////////////
        // Geometry
        //////////////////////////////////////////


        if(entities[i]->returnType() == "geometry" && entities[i]->returnEnableRender() == true)
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
            
            entitiesShader.activate();
            entitiesShader.setMat4("projection", projection);
            entitiesShader.setMat4("view", view);
            entitiesShader.setVec3("color", entities[i]->returnColor() );
            entitiesShader.setMat4("model", model);

            entities[i]->returnGeometry()->draw(entitiesShader);
        }


    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    // END World Render
    ///////////////////////////////////////////////////////////////////////////////////////////






    


    

    ///////////////////////////////////////////////////////////////////////////////////////////
    // START Overlay Models
    ///////////////////////////////////////////////////////////////////////////////////////////

    for(int i=0; i<entities.size(); i++)
    {
        if(entities[i]->returnType() == "overlay" && entities[i]->returnEnableRender() == true)
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
    // END Overlay Models
    ///////////////////////////////////////////////////////////////////////////////////////////








    ///////////////////////////////////////////////////////////////////////////////////////////
    // START Overlay Sprites
    ///////////////////////////////////////////////////////////////////////////////////////////

    for(int i=0; i<entities.size(); i++)
    {
        if(entities[i]->returnType() == "sprite" && entities[i]->returnEnableRender() == true)
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

    ///////////////////////////////////////////////////////////////////////////////////////////
    // END Overlay Sprites
    ///////////////////////////////////////////////////////////////////////////////////////////




    glfwSwapBuffers(window);
    glfwPollEvents(); 
};






















void Graphics::animation(Entity* entity, Shader& entitiesShader)
{
    ////////////////////////////////////////////////////////////////////////////
    // START Animation
    ////////////////////////////////////////////////////////////////////////////
    
    if(entity->returnModel()->animation != nullptr)
    {
        ////////////////////////////////////////////////////
        // Part 1 Refresh Final Bones
        ////////////////////////////////////////////////////
        for (size_t b = 0; b < entity->finalBones.size(); ++b)
        {
            entity->finalBones[b] = glm::mat4(1.0f);
        }

        ////////////////////////////////////////////////////
        // Part 2 Get Local Bone Transformation
        ////////////////////////////////////////////////////

        std::map<std::string, glm::mat4> animatedLocalTransforms;
        
        entity->time += deltaTime;

        float ticksPerSecond = entity->returnModel()->animation->mTicksPerSecond;
        if (ticksPerSecond == 0.0f)
            ticksPerSecond = 1.0f;

        float ticks = fmod(entity->time * ticksPerSecond, entity->returnModel()->animation->mDuration);
        if(ticksPerSecond > 100) ticksPerSecond = 1.0f;

        if (entity->returnModel()->animation->mChannels == nullptr || entity->returnModel()->animation->mNumChannels == 0)
        {

            for (unsigned chIdx = 0; chIdx < entity->returnModel()->animation->mNumChannels; chIdx++)
            {
                aiNodeAnim* channel = entity->returnModel()->animation->mChannels[chIdx];

                if (!channel) continue;

                const char* nodeName = channel->mNodeName.C_Str();
                if (!nodeName) continue;

                
                auto it = entity->returnModel()->boneMap.find(nodeName);
                if (it == entity->returnModel()->boneMap.end()) continue;

                int boneIndex = it->second;

                if (boneIndex >= entity->finalBones.size() || boneIndex >= entity->returnModel()->boneOffsets.size()) continue;
                if (channel->mNumPositionKeys == 0 || channel->mNumRotationKeys == 0) continue;
                
                // --- Interpolate Position ---
                unsigned posIndex = 0;
                while (posIndex + 1 < channel->mNumPositionKeys &&
                    channel->mPositionKeys[posIndex + 1].mTime <= ticks) posIndex++;

                aiVector3D pos = channel->mPositionKeys[posIndex].mValue;
                if(posIndex + 1 < channel->mNumPositionKeys) // interpolate to next key
                {
                    aiVector3D nextPos = channel->mPositionKeys[posIndex + 1].mValue;
                    float t0 = channel->mPositionKeys[posIndex].mTime;
                    float t1 = channel->mPositionKeys[posIndex + 1].mTime;
                    float factor = (ticks - t0) / (t1 - t0);
                    pos = pos + (nextPos - pos) * factor; // linear interpolation
                }

                // --- Interpolate Rotation using aiQuaternion::Interpolate (fix) ---
                unsigned rotIndex = 0;
                while (rotIndex + 1 < channel->mNumRotationKeys &&
                    channel->mRotationKeys[rotIndex + 1].mTime <= ticks) rotIndex++;

                aiQuaternion rot;
                if(rotIndex + 1 < channel->mNumRotationKeys) // interpolate to next key
                {
                    aiQuaternion startRot = channel->mRotationKeys[rotIndex].mValue;
                    aiQuaternion endRot   = channel->mRotationKeys[rotIndex + 1].mValue;
                    float t0 = channel->mRotationKeys[rotIndex].mTime;
                    float t1 = channel->mRotationKeys[rotIndex + 1].mTime;
                    float factor = (ticks - t0) / (t1 - t0);

                    aiQuaternion::Interpolate(rot, startRot, endRot, factor); // Correct Assimp usage
                }
                else
                {
                    rot = channel->mRotationKeys[rotIndex].mValue;
                }

                // --- Interpolate Scale ---
                aiVector3D scale(1, 1, 1);
                if (channel->mNumScalingKeys > 0) {
                    unsigned sclIndex = 0;
                    while (sclIndex + 1 < channel->mNumScalingKeys && channel->mScalingKeys[sclIndex + 1].mTime <= ticks) sclIndex++;
                    scale = channel->mScalingKeys[sclIndex].mValue;
                    // ... optional: add interpolation logic like you did for pos/rot ...
                }

                glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));
                glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
                glm::mat4 R = glm::mat4_cast(glm::quat(rot.w, rot.x, rot.y, rot.z));

                animatedLocalTransforms[nodeName] = T * R * S; // Order matters: TRS
            }

            ////////////////////////////////////////////////////
            // Part 3 Determine Heirarchies Traversal
            ////////////////////////////////////////////////////
            
            //Need to add a Parent Child Heirarchie to Bones
            //This comes after all the bones have been accounted for
            struct NodeStackEntry
            {
                aiNode* node;
                glm::mat4 parentTransform;
            };
            std::vector<NodeStackEntry> stack;


            //Start traversal at the scene root
            //Root has no parent → identity transform
            stack.push_back({ entity->returnModel()->scene->mRootNode, glm::mat4(1.0f) });

            while(!stack.empty())
            {
                NodeStackEntry entry = stack.back();
                stack.pop_back();
                aiNode* node = entry.node;
                glm::mat4 parentTransform = entry.parentTransform;

                // Convert this node’s local transform
                // This is the transform relative to its parent
                glm::mat4 nodeTransform = glm::transpose(glm::mat4(
                    node->mTransformation.a1, node->mTransformation.b1, node->mTransformation.c1, node->mTransformation.d1,
                    node->mTransformation.a2, node->mTransformation.b2, node->mTransformation.c2, node->mTransformation.d2,
                    node->mTransformation.a3, node->mTransformation.b3, node->mTransformation.c3, node->mTransformation.d3,
                    node->mTransformation.a4, node->mTransformation.b4, node->mTransformation.c4, node->mTransformation.d4
                ));

                auto animIt = animatedLocalTransforms.find(node->mName.C_Str());
                if (animIt != animatedLocalTransforms.end())
                {
                    nodeTransform = animIt->second;
                }

                // This is a Global Transform = Parent * Local
                // This is where hierarchy is enforced
                glm::mat4 globalTransform = parentTransform * nodeTransform;


                // If this node corresponds to a mesh bone,
                // compute the final matrix used for skinning
                auto it = entity->returnModel()->boneMap.find(node->mName.C_Str());
                if(it != entity->returnModel()->boneMap.end())
                {
                    unsigned index = it->second;

                    // Final bone matrix:
                    // global node transform * inverse bind pose (offset)
                    if (index < entity->finalBones.size() && index < entity->returnModel()->boneOffsets.size())
                    {
                        entity->finalBones[index] = globalTransform * entity->returnModel()->boneOffsets[index];
                    }
                }

                // Push children so they inherit this node’s global transform
                for(unsigned j = 0; j < node->mNumChildren; j++)
                {
                    stack.push_back({ node->mChildren[j], globalTransform });
                }

            }

            ////////////////////////////////////////////////////
            // Part 4 Send data To Shader
            ////////////////////////////////////////////////////


            for (int b = 0; b < entity->finalBones.size(); b++)
            {
                entitiesShader.setMat4("bones[" + std::to_string(b) + "]", entity->finalBones[b]);
            }
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // END Animation
    ////////////////////////////////////////////////////////////////////////////
};