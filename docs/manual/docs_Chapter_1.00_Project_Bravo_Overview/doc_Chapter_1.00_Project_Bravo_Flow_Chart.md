# NAVIGATION
- 🏠 [Home](../../../README.md)
- 📖 [Table of Contents](../docs_Chapter_0.00_Welcome/doc_Chapter_0.10_Table_of_Contents.md)

# Note
- Best to open in a Text Editor or on Github's Code tab

# Project Layout

Source Code
     |
     |
     |
src/include --- Note: Contains header files and cpp files
     |
     |
     |
    App---------------------
                           |
                           |
                           |
             Game <--------|--------> Network
                           |            |
                           |            |
                           |            |------> Netowrk Server
                           |            |------> Network Client
                           |
                           |
                           |       
                           |------> Engine
                                       |
                                       |
                                       |------> Audio --- Note: Audio Pipeline
                                       |------> Audio File --- Note: Read Audio File and output 16bit vector<float>
                                       |
                                       |------> Entity --- Note: Everything in the engine is consider a entity
                                       |          |
                                       |          |
                                       |          |------> Entity
                                       |          |------> Camera
                                       |          |------> Geometry
                                       |          |------> Model
                                       |          |------> Sprite
                                       |          
                                       |------> Graphics --- Note: Handle rendering pipeline for OpenGL
                                       |          |
                                       |          |
                                       |          |------> Opengl
                                       |                      |
                                       |                      |
                                       |                      |------> Graphics
                                       |                      |------> Mesh
                                       |                      |------> Shader
                                       |
                                       |
                                       |------> Physics --- Note: Controls anythings related to Physics and Collisions
                                       |          |
                                       |          |
                                       |          |------> Collider
                                       |          |------> Collision
                                       |          |------> Raycast
                                       |          |------> Rigid Body
                                       |
                                       |------> Scene --- Note: Asset Loading and Scene Entity Loading
                                       |          |
                                       |          |
                                       |          |------> Entity Load
                                       |          |------> Entity Save
                                       |          |------> Config Load
                                       |
                                       |------> User --- Note: User Device Interfaces
                                                  |
                                                  |
                                                  |------> Keyboard
                                                  |------> Mouse