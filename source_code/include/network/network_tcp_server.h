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

    NetworkServerTCP()
    {
        WSADATA wsaData;
        if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
        {
            std::cerr << "SERVER_RECEIVER::ERROR::WSA_STARTUP_FAILED" << std::endl;
        }

        serverReceiverSocket = socket(AF_INET, SOCK_STREAM, 0);

        if(serverReceiverSocket == -1)
        {
            std::cerr << "SERVER_RECEIVER::ERROR::FAILED_TO_CREATE_SOCKET" << std::endl;
            WSACleanup();
        }

        sockaddr_in serverReceiverAddress;
        serverReceiverAddress.sin_family = AF_INET;
        serverReceiverAddress.sin_port = htons(8080);
        serverReceiverAddress.sin_addr.s_addr = INADDR_ANY;
        
        if( bind(serverReceiverSocket, (struct sockaddr*)&serverReceiverAddress, sizeof(serverReceiverAddress)) == SOCKET_ERROR )
        {
            std::cerr << "SERVER_RECIEVER::ERROR::FAILED_TO_BIND::CODE::" + std::to_string(WSAGetLastError()) << std::endl;
            closesocket(serverReceiverSocket);
            WSACleanup();
        }
        
        if(listen(serverReceiverSocket, 5) == SOCKET_ERROR)
        {
            std::cerr << "SERVER_RECEIVER::ERROR::FAILED_TO_LISTEN::CODE::" << std::to_string(WSAGetLastError()) << std::endl;
            closesocket(serverReceiverSocket);
            WSACleanup();
        }

        std::cout << "SERVER_RECEIVER::SERVER_STARTED" << std::endl;

        std::thread thread_reciever(&NetworkServerTCP::serverMainLoop, this);
        thread_reciever.detach();
    };

    ~NetworkServerTCP()
    {
        closesocket(serverReceiverSocket);
        WSACleanup();
        std::cout << "SERVER_RECEIVER::SERVER_ENDED" << std::endl;
    };

    //////////////////////////////////////
    // PHASE 1 Start 8080 Server
    //////////////////////////////////////
    void serverMainLoop()
    {   
        while(true)
        {
            sockaddr_in clientSenderAddress;
            int clientSenderSize = sizeof(clientSenderAddress);

            SOCKET clientSenderSocket = accept( serverReceiverSocket, (sockaddr*)&clientSenderAddress, &clientSenderSize);
            std::cout << "SERVER_RECEIVER::CLIENT_SENDER_CONNECTED\n" << std::endl;

            std::thread thread_reciever(&NetworkServerTCP::clientHandle_receiver, this, clientSenderSocket, clientSenderAddress);
            thread_reciever.detach();
        }
    };

    //////////////////////////////////////
    // PHASE 4 Receiving 8080
    //////////////////////////////////////
    void clientHandle_receiver(SOCKET clientSenderSocket, sockaddr_in clientSenderAddress)
    {
        // ######################################################################################
        // Start Client Handle
        // ######################################################################################
        
        char initiateBuffer[1024] = {};
        recv( clientSenderSocket, initiateBuffer, sizeof(initiateBuffer), 0);
        
        std::string initiateData = initiateBuffer;
        std::stringstream ss(initiateData);

        std::string setPlayer = "0";
        std::string setPlayer_action = "0";

        std::getline(ss, setPlayer, ',');
        std::getline(ss, setPlayer_action, ',');

        std::thread thread_sender(&NetworkServerTCP::clientHandle_sender, this, std::stoi(setPlayer), clientSenderAddress);
        thread_sender.detach();

        while(true)
        {
            ////////////////////////////////////////////////////////////////////////////////////////
            // Options
            ////////////////////////////////////////////////////////////////////////////////////////
            //
            // player_id : 0 = Player 1 | 1 = Player 2
            // player_action : 0 = NULL | -1 = Exit
            // player_movement : 0 = NULL | 1 = Forward | 2 = Backward | 3 = Left | 4 = Right
            //
            // Message String Example
            // Ex: int player_id, int player_action, int player_command_movement
            // Ex: 0,0,0
            //
            ////////////////////////////////////////////////////////////////////////////////////////

            // Note: Server Receives Player's Action Here

            // 1. Receiving Message
            char buffer[1024] = {};
            recv( clientSenderSocket, buffer, sizeof(buffer), 0);
            
            std::string data = buffer;

            // 2. Reading Message
            std::stringstream ss(data);
            
            std::string player = "0";
            std::string player_action = "0";

            std::getline(ss, player, ',');
            std::getline(ss, player_action, ',');

            // 3. Executing Message
            if(player=="1")
            {
                if(player_action=="1"){player_1_cameraPosition += glm::vec3( 0.0f , 0.0f,-0.00005f);} // W
                if(player_action=="2"){player_1_cameraPosition += glm::vec3( 0.0f , 0.0f, 0.00005f);} // S
                if(player_action=="3"){player_1_cameraPosition += glm::vec3(-0.00005f, 0.0f, 0.0f);} // A
                if(player_action=="4"){player_1_cameraPosition += glm::vec3( 0.00005f, 0.0f, 0.0f);} // D
                if(player_action=="5"){player_1_cameraPosition += glm::vec3( 0.0f, 0.00005f, 0.0f);} // A
                if(player_action=="6"){player_1_cameraPosition += glm::vec3( 0.0f,-0.00005f, 0.0f);} // D
            }

            if(player=="2")
            {
                if(player_action=="1"){player_2_cameraPosition += glm::vec3( 0.0f , 0.0f,-0.00005f);} // W
                if(player_action=="2"){player_2_cameraPosition += glm::vec3( 0.0f , 0.0f, 0.00005f);} // S
                if(player_action=="3"){player_2_cameraPosition += glm::vec3(-0.00005f, 0.0f, 0.0f);} // A
                if(player_action=="4"){player_2_cameraPosition += glm::vec3( 0.00005f, 0.0f, 0.0f);} // D
                if(player_action=="5"){player_2_cameraPosition += glm::vec3( 0.0f, 0.00005f, 0.0f);} // A
                if(player_action=="6"){player_2_cameraPosition += glm::vec3( 0.0f,-0.00005f, 0.0f);} // D
            }
        }

        closesocket(clientSenderSocket);
        std::cout << "SERVER_RECEIVER::DISCONNECTED_FROM_CLIENT_SENDER" << std::endl;
    }

    //////////////////////////////////////
    // PHASE 5 Connect to 8081 Server
    //////////////////////////////////////
    void clientHandle_sender(int setPlayer, sockaddr_in clientSenderAddress)
    {

        SOCKET serverSenderSocket = socket(AF_INET,SOCK_STREAM,0);

        if(serverSenderSocket == -1)
        {
            WSACleanup();
            std::cerr << "SERVER_SENDER::ERROR::FAILED_TO_CREATE_SOCKET" << std::endl;
            return;
        }

        char ipstr[INET_ADDRSTRLEN];
        inet_ntop( AF_INET, &clientSenderAddress.sin_addr, ipstr, INET_ADDRSTRLEN );

        const char* HOST_IP = ipstr;

        sockaddr_in clientReceiverAddress;
        clientReceiverAddress.sin_family = AF_INET;
        clientReceiverAddress.sin_port = htons(8081);
        clientReceiverAddress.sin_addr.s_addr = inet_addr(HOST_IP);

        connect(serverSenderSocket, (struct sockaddr*)&clientReceiverAddress, sizeof(clientReceiverAddress));
        std::cout << "SERVER_SENDER::CONNECTED_TO_CLIENT_RECEIVER::" << clientReceiverAddress.sin_addr.s_addr << "\n" <<  std::endl;

        int player = setPlayer;
        
        while(true)
        {
            // Note: Server is going to send player position info, along with other players info for rendering
            std::string data;

            data = std::to_string(player_1_cameraPosition.x) + ',' + std::to_string(player_1_cameraPosition.y) + ',' + std::to_string(player_1_cameraPosition.z) + ',' + 
            std::to_string(player_2_cameraPosition.x) + ',' + std::to_string(player_2_cameraPosition.y) + ',' + std::to_string(player_2_cameraPosition.z);
           
            const char* message = data.c_str();

            int result = send(serverSenderSocket, message, strlen(message), 0);
            if (result == SOCKET_ERROR)
            {
                std::cerr << "SERVER_SENDER::ERROR::SEND_FAILED" << std::endl;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        closesocket(serverSenderSocket);
        WSACleanup();

        std::cout << "SERVER_SENDER::DISCONNECTED_FROM_CLIENT_RECEIVER" << std::endl;
    };
};

#endif