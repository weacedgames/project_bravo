#ifndef NETWORK_CLIENT_H
#define NETWOKR_CLIENT_H

#include <iostream>
#include <windows.h>
#include <winsock.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma comment(lib,"ws2_32.lib")

class NetworkClient
{
public:
    glm::vec3 playerPosition;

    glm::vec3 cameraPosition;
    glm::vec3 cameraDirection;

    bool trigger;

    float health;

public:
    NetworkClient()
    {
         WSADATA wsaData;

        if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
            std::cerr << "ERROR::WSA_STARTUP_FAILED" << std::endl;
        }
        SOCKET clientSocket = socket(AF_INET,SOCK_STREAM,0);
        if(clientSocket == -1){
            WSACleanup();
            std::cerr << "ERROR::FAILED_TO_CREATE_SOCKET" << std::endl;
        }

        const char* HOST_IP = "127.0.0.1";

        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = inet_addr(HOST_IP);
        
        connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
        std::cout << "CLIENT::CONNECTED_TO::" << HOST_IP << std::endl;

        const char* message = "move,0,ace,0.0,0.0,0.0";

        send(clientSocket, message, strlen(message), 0);
        std::cout << "CLIENT::SENDING::" << message << std::endl;

        closesocket(clientSocket);
        WSACleanup();

        std::cout << "CLIENT::DISCONNECTED" << std::endl;
    };

};

#endif