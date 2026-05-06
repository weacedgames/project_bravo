#ifndef NETWORK_TCP_CLIENT_H
#define NETWOKR_TCP_CLIENT_H

#include <iostream>
#include <windows.h>
#include <winsock.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <sstream>
#include <thread>
#include <vector>

#pragma comment(lib,"ws2_32.lib")

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Protocol
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        |  Phase 1  | Server: Start 8080 Server
// CLIENT: Start 8081 Server              |  Phase 2  | 
// CLIENT: Connect to 8080 Server         |  Phase 3  |
//                                        |  Phase 4  | SERVER: Receive 8080 Client Connection for action
//                                        |  Phase 5  | SERVER: Connect to 8081 Server
// CLIENT: Receive 8081 Server Connection |  Phase 6  |
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////


class NetworkClientTCP
{
public:
    SOCKET clientReceiverSocket;
    sockaddr_in clientReceiverAddress;

    const char* HOST_IP = "";

    int selectedPlayer = 0;

    int player_1_action = 0;
    glm::vec3 player_1_position = glm::vec3(0.0f, 0.0f, 0.0f);        
    glm::vec3 player_1_cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    int player_2_action = 0;
    glm::vec3 player_2_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 player_2_cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

public:
    NetworkClientTCP(int setPlayer);
    ~NetworkClientTCP();

public:
    //////////////////////////////////////
    // PHASE 6 Receiving 8081
    //////////////////////////////////////
    void serverHandle_receiver();

    //////////////////////////////////////
    // PHASE 3 Connect to 8080 Server
    //////////////////////////////////////
    void serverHandle_sender();

};

#endif