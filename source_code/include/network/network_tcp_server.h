#ifndef NETWORK_TCP_SERVER_H
#define NETWORK_TCP_SERVER_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>
#include <thread>
#include <vector>

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>

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

class NetworkServerTCP
{
public:
    SOCKET serverReceiverSocket;
    sockaddr_in serverReceiverAddress;

    glm::vec3 player_1_position = glm::vec3(0.0f, 0.0f, 0.0f);        
    glm::vec3 player_1_cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 player_2_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 player_2_cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

public:
    NetworkServerTCP();
    ~NetworkServerTCP();
    
public:
    //////////////////////////////////////
    // PHASE 1 Start 8080 Server
    //////////////////////////////////////
    void serverMainLoop();

    //////////////////////////////////////
    // PHASE 4 Receiving 8080
    //////////////////////////////////////
    void clientHandle_receiver(SOCKET clientSenderSocket, sockaddr_in clientSenderAddress);

    //////////////////////////////////////
    // PHASE 5 Connect to 8081 Server
    //////////////////////////////////////
    void clientHandle_sender(int setPlayer, sockaddr_in clientSenderAddress);
};

#endif