#include "network_udp_client.h"

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

NetworkClientUDP::NetworkClientUDP(int setPlayer)
{
    //////////////////////////////////////
    // PHASE 2 Start 8081 Server
    //////////////////////////////////////
    
    selectedPlayer = setPlayer;

    if(selectedPlayer==1)
    {
        HOST_IP = "127.0.0.1";
    }

    if(selectedPlayer==2)
    {
        HOST_IP = "192.168.0.242";
    }

    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        std::cerr << "CLIENT_RECEIVER::ERROR::WSA_STARTUP_FAILED" << std::endl;
    }

    clientReceiverSocket = socket(AF_INET, SOCK_DGRAM, 0);

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
    
    std::cout << "CLIENT_RECEIVER::SERVER_STARTED" << std::endl;
    std::cout << "---------------------------------------------------------------\n" << std::endl;

    ///////////////////////////////////////////////////////////////////////////

    // Phase 2
    std::thread thread_receiver(&NetworkClientUDP::serverHandle_receiver, this);
    thread_receiver.detach();

    // Phase 3
    std::thread thread_sender(&NetworkClientUDP::serverHandle_sender, this);
    thread_sender.detach();
};

NetworkClientUDP::~NetworkClientUDP()
{
    closesocket(clientReceiverSocket);
    WSACleanup();
    std::cout << "SERVER_RECEIVER::SERVER_ENDED" << std::endl;
};


//////////////////////////////////////
// PHASE 3 Connect to 8080 Server
//////////////////////////////////////
void NetworkClientUDP::serverHandle_sender()
{
    SOCKET clientSenderSocket = socket(AF_INET,SOCK_DGRAM,0);

    if(clientSenderSocket == -1)
    {
        WSACleanup();
        std::cerr << "CLIENT_SENDER::ERROR::FAILED_TO_CREATE_SOCKET" << std::endl;
    }

    sockaddr_in serverReceiverAddress;
    serverReceiverAddress.sin_family = AF_INET;
    serverReceiverAddress.sin_port = htons(8080);
    serverReceiverAddress.sin_addr.s_addr = inet_addr(HOST_IP);

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
        int message_len = (int)strlen(message);
        int server_addr_len = sizeof(serverReceiverAddress);

        int result = sendto(clientSenderSocket, message, message_len, 0, (sockaddr*)&serverReceiverAddress, server_addr_len);
        if (result == SOCKET_ERROR)
        {
            std::cerr << "SERVER_SENDER::ERROR::SEND_FAILED" << std::endl;
            std::cerr << WSAGetLastError() << std::endl;
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
};


//////////////////////////////////////
// PHASE 6 Receiving 8081
//////////////////////////////////////
void NetworkClientUDP::serverHandle_receiver()
{
    while(true)
    {
        // Note:: Client receive info on players positions for rendering
        char buffer[1024] = {};
        int server_addr_len = sizeof(serverSenderAddress);
        recvfrom( clientReceiverSocket, buffer, sizeof(buffer), 0, (sockaddr*)&serverSenderAddress, &server_addr_len);

        std::string data = buffer;

        std::string xPos_1 = "0"; 
        std::string yPos_1 = "0";
        std::string zPos_1 = "0";

        std::string xPos_2 = "0"; 
        std::string yPos_2 = "0";
        std::string zPos_2 = "0"; 

        std::stringstream ss(data);

        std::getline(ss, xPos_1, ',');
        std::getline(ss, yPos_1, ',');
        std::getline(ss, zPos_1, ',');

        std::getline(ss, xPos_2, ',');
        std::getline(ss, yPos_2, ',');
        std::getline(ss, zPos_2, ',');

        player_1_cameraPosition = glm::vec3( std::stof(xPos_1), std::stof(yPos_1), std::stof(zPos_1) );
        player_2_cameraPosition = glm::vec3( std::stof(xPos_2), std::stof(yPos_2), std::stof(zPos_2) );
    }

    std::cout << "CLIENT_RECEIVER::DISCONNECTED_FROM_SERVER_SENDER" << std::endl;
};