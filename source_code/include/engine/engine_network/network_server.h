#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <windows.h>
#include <winsock.h>
#include <string>
#include <sstream>
#include <thread>
#include <vector>

class NetworkServer
{
private:
    std::vector<std::string> SERVER_MESSAGES;

    std::vector<int> players_id = {0};
    std::vector<std::string> players_username = {"ace"};
    std::vector<glm::vec3> players_position = {glm::vec3(0.0f, 0.0f, 0.0f)};

private:
    void run(SOCKET serverSocket);

public:
    NetworkServer();

public:
    void addPlayer(int player_id, std::string username, glm::vec3 position);

public:
    void removePlayer(int player_id);

public:
    void updatePlayerId(int player_id, int setId);
    void updatePlayerUsername(int player_id, std::string setUsername);
    void updatePlayerPosition(int player_id, glm::vec3 setPosition);

public:
    int returnPlayerId(int player_id);
    glm::vec3 returnPlayerPosition(int player_id);
    std::string returnPlayerUsername(int player_id);
    std::vector<std::string> return_server_messages();
};

#endif