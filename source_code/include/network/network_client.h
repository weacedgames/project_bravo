#ifndef NETWORK_CLIENT_H
#define NETWOKR_CLIENT_H

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

class NetworkClient
{
public:
    SOCKET clientReceiverSocket;
    sockaddr_in clientReceiverAddress;

    int selectedPlayer = 0;

    int player_1_action = 0;
    glm::vec3 player_1_position = glm::vec3(0.0f, 0.0f, 0.0f);        
    glm::vec3 player_1_cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    int player_2_action = 0;
    glm::vec3 player_2_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 player_2_cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

public:
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


    NetworkClient(int setPlayer)
    {
        //////////////////////////////////////
        // PHASE 2 Start 8081 Server
        //////////////////////////////////////
        
        selectedPlayer = setPlayer;

        WSADATA wsaData;

        if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
        {
            std::cerr << "CLIENT_RECEIVER::ERROR::WSA_STARTUP_FAILED" << std::endl;
        }

        clientReceiverSocket = socket(AF_INET, SOCK_STREAM, 0);

        if(clientReceiverSocket == -1)
        {
            std::cerr << "CLIENT_RECEIVER::ERROR::FAILED_TO_CREATE_SOCKET" << std::endl;
            WSACleanup();
        }

        clientReceiverAddress;
        clientReceiverAddress.sin_family = AF_INET;
        clientReceiverAddress.sin_port = htons(8081);
        clientReceiverAddress.sin_addr.s_addr = INADDR_ANY;
        
        if( bind(clientReceiverSocket, (struct sockaddr*)&clientReceiverAddress, sizeof(clientReceiverAddress)) == SOCKET_ERROR )
        {
            std::cerr << "CLIENT_RECEIVER::ERROR::FAILED_TO_BIND::CODE::" + std::to_string(WSAGetLastError()) << std::endl;
            closesocket(clientReceiverSocket);
            WSACleanup();
        }
        
        if(listen(clientReceiverSocket, 5) == SOCKET_ERROR)
        {
            std::cerr << "CLIENT_RECEIVER::ERROR::FAILED_TO_LISTEN::CODE::" << std::to_string(WSAGetLastError()) << std::endl;
            closesocket(clientReceiverSocket);
            WSACleanup();
        }

        std::cout << "CLIENT_RECEIVER::SERVER_STARTED" << std::endl;


        ///////////////////////////////////////////////////////////////////////////

        // Phase 2
        std::thread thread_receiver(&NetworkClient::serverHandle_receiver, this);
        thread_receiver.detach();

        // Phase 3
        std::thread thread_sender(&NetworkClient::serverHandle_sender, this);
        thread_sender.detach();
    };

    ~NetworkClient()
    {
        closesocket(clientReceiverSocket);
        WSACleanup();
        std::cout << "SERVER_RECEIVER::SERVER_ENDED" << std::endl;
    };

    //////////////////////////////////////
    // PHASE 6 Receiving 8081
    //////////////////////////////////////
    void serverHandle_receiver()
    {
        sockaddr_in serverSenderAddress;
        int serverSenderSize = sizeof(serverSenderAddress);
        SOCKET serverSenderSocket = accept( clientReceiverSocket, (sockaddr*)&serverSenderAddress, &serverSenderSize);
        std::cout << "CLIENT_RECEIVER::SERVER_SENDER_CONNECTED" << std::endl;

        while(true)
        {
            // Note:: Client receive info on players positions for rendering
            char buffer[1024] = {};
            int bytesReceived = recv(serverSenderSocket, buffer, sizeof(buffer), 0);
            

            if (bytesReceived == SOCKET_ERROR)
            {
                std::cerr << "CLIENT_RECEIVER::ERROR::RECV_FAILED" << std::endl;
                break;  // Exit loop if there was an error with receiving data
            }
            else if (bytesReceived == 0)
            {
                std::cout << "CLIENT_RECEIVER::SERVER_CLOSED_CONNECTION" << std::endl;
                break;  // Exit loop if the server closed the connection
            }

            std::string data = buffer;

            std::string xPos = "0"; 
            std::string yPos = "0";
            std::string zPos = "0"; 

            std::stringstream ss(data);

            std::getline(ss, xPos, ',');
            std::getline(ss, yPos, ',');
            std::getline(ss, zPos, ',');

            // 3. Executing Message
            if(selectedPlayer == 1)
            {
                player_1_cameraPosition = glm::vec3( std::stof(xPos), std::stof(yPos), std::stof(zPos) );
            }

            if(selectedPlayer == 2)
            {
                player_2_cameraPosition = glm::vec3( std::stof(xPos), std::stof(yPos), std::stof(zPos) );
            }

            //std::cout << "SERVER_SENDER::RECIEVED::" << data << std::endl;
        }
        
        closesocket(serverSenderSocket);
        std::cout << "CLIENT_RECEIVER::DISCONNECTED_FROM_SERVER_SENDER" << std::endl;
    };

    //////////////////////////////////////
    // PHASE 3 Connect to 8080 Server
    //////////////////////////////////////
    void serverHandle_sender()
    {
        SOCKET clientSenderSocket = socket(AF_INET,SOCK_STREAM,0);

        if(clientSenderSocket == -1)
        {
            WSACleanup();
            std::cerr << "CLIENT_SENDER::ERROR::FAILED_TO_CREATE_SOCKET" << std::endl;
        }

        const char* HOST_IP = "127.0.0.1";

        sockaddr_in serverReceiverAddress;
        serverReceiverAddress.sin_family = AF_INET;
        serverReceiverAddress.sin_port = htons(8080);
        serverReceiverAddress.sin_addr.s_addr = inet_addr(HOST_IP);

        connect(clientSenderSocket, (struct sockaddr*)&serverReceiverAddress, sizeof(serverReceiverAddress));
        std::cout << "CLIENT_SENDER::CONNECTED_TO_SERVER_RECEIVER::" << serverReceiverAddress.sin_addr.s_addr << std::endl;

        

        while(true)
        {   
            // Note: Send Player Actions
            std::string action;
            
            if(selectedPlayer==1)
            {
                action = "1," + std::to_string(player_1_action);
            }
            
            if(selectedPlayer==2)
            {
                action = "2," + std::to_string(player_2_action);
            }

            const char* message = action.c_str();

            send(clientSenderSocket, message, strlen(message), 0);
            //std::cout << "CLIENT_SENDER::SENDING::" << message << std::endl;
        }

        closesocket(clientSenderSocket);
        WSACleanup();

        std::cout << "CLIENT_SENDER::DISCONNECTED_FROM_SERVER_RECEIVER" << std::endl;
    };

};

#endif