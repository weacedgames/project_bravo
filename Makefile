# Section 1: Declaring External Libraries

glfw_include = ./source_code/libraries/GLFW/include
glfw_lib = ./source_code/libraries/GLFW/lib

assimp_include = ./source_code/libraries/ASSIMP/include
assimp_lib = ./source_code/libraries/ASSIMP/lib

glad_include = ./source_code/libraries/GLAD/include
glad_src =  ./source_code/libraries/GLAD/src/glad.c

stb_include = ./source_code/libraries/STB/include
stb_src = ./source_code/libraries/STB/src/stb.cpp

glm_include = ./source_code/libraries/GLM/include

json_include = ./source_code/libraries/JSON/include

EXTERNAL_DEPENDCIES = -I$(glfw_include) -I$(glad_include) -I$(stb_include) -I$(glm_include) -I$(json_include) -I$(assimp_include)

################################################################################################################################################################################################################################
# Section 2: Declaring Header Files

path_include_graphics = ./source_code/include/engine/engine_graphics
path_include_entity = ./source_code/include/engine/engine_entity
path_include_project = ./source_code/include/engine/engine_scene
path_include_network = ./source_code/include/engine/engine_network
path_include_physics = ./source_code/include/engine/engine_physics
path_include_user = ./source_code/include/engine/engine_user

ENGINE_DEPENDCIES = -I$(path_include_graphics)/opengl -I$(path_include_entity) -I$(path_include_project) -I$(path_include_network) -I$(path_include_physics) -I$(path_include_user)


path_include_game = ./source_code/include/game
GAME_DEPENDCIES = -I$(path_include_game)

LOCAL_DEPENDCIES = $(ENGINE_DEPENDCIES) $(GAME_DEPENDCIES)

################################################################################################################################################################################################################################
# Section 3: Declaring Source Files

path_src_graphics = ./source_code/src/engine/engine_graphics
local_src_graphics_opengl = $(path_src_graphics)/opengl/graphics.cpp $(path_src_graphics)/opengl/shader.cpp $(path_src_graphics)/opengl/mesh.cpp 


path_src_entity = ./source_code/src/engine/engine_entity
local_src_entity_entity = $(path_src_entity)/entity.cpp $(path_src_entity)/model.cpp $(path_src_entity)/geometry.cpp $(path_src_entity)/camera.cpp $(path_src_entity)/sprite.cpp


path_src_physics = ./source_code/src/engine/engine_physics
local_src_physics =  $(path_src_physics)/rigid_body.cpp $(path_src_physics)/collider.cpp $(path_src_physics)/collision.cpp $(path_src_physics)/raycast.cpp


path_src_engineScene = ./source_code/src/engine/engine_scene
local_src_engineScene = $(path_src_engineScene)/scene_save.cpp $(path_src_engineScene)/scene_load.cpp $(path_src_engineScene)/config_load.cpp


path_src_engineNetwork = ./source_code/src/engine/engine_network
local_src_engineNetwork = $(path_src_engineNetwork)/network_server.cpp

path_src_engineUser = ./source_code/src/engine/engine_user
local_src_engineUser = $(path_src_engineUser)/keyboard.cpp $(path_src_engineUser)/mouse.cpp

ENGINE_SOURCE = $(local_src_graphics_opengl) $(local_src_entity_entity) $(local_src_physics) $(local_src_engineScene) $(local_src_engineNetwork) $(local_src_engineUser)

path_src_game = ./source_code/src/game
local_src_game = $(path_src_game)/game.cpp

GAME_SOURCE = $(local_src_game)

LOCAL_SOURCE = $(ENGINE_SOURCE) $(GAME_SOURCE)


#################################################################################
# Section 4: Execute Program

CXX = g++
CPP = ./source_code/src/app/main.cpp
TARGET = ./bin/main

OBJECTS = $(CPP) $(glad_src) $(stb_src) $(LOCAL_SOURCE)
INCLUDES = $(EXTERNAL_DEPENDCIES) $(LOCAL_DEPENDCIES)
libRARIES = -L$(glfw_lib) -L$(assimp_lib)

C_FLAGS = $(INCLUDES)
LD_FLAGS = $(libRARIES) -lws2_32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lassimp -lwinmm

$(TARGET): $(CPP) # Final Output
	$(CXX) $(OBJECTS) $(C_FLAGS) $(LD_FLAGS) -o$(TARGET)