#include "network_udp_server.h"

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

NetworkServerUDP::NetworkServerUDP()
{
    //////////////////////////////////////
    // PHASE 1 Start 8080 Server
    //////////////////////////////////////
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        std::cerr << "SERVER_RECEIVER::ERROR::WSA_STARTUP_FAILED" << std::endl;
    }

    serverReceiverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(serverReceiverSocket == INVALID_SOCKET)
    {
        std::cerr << "SERVER_RECEIVER::ERROR::FAILED_TO_CREATE_SOCKET" << std::endl;
        WSACleanup();
        return;
    }

    serverSenderSocket = socket(AF_INET,SOCK_DGRAM,0);
    if(serverSenderSocket == INVALID_SOCKET)
    {
        WSACleanup();
        std::cerr << "SERVER_SENDER::ERROR::FAILED_TO_CREATE_SOCKET" << std::endl;
        return;
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
    
    std::cout << "SERVER_RECEIVER::SERVER_STARTED" << std::endl;
    std::cout << "---------------------------------------------------------------\n" << std::endl;

    std::thread thread_reciever(&NetworkServerUDP::server_mainloop, this);
    thread_reciever.detach();
};

NetworkServerUDP::~NetworkServerUDP()
{
    closesocket(serverReceiverSocket);
    closesocket(serverSenderSocket);
    WSACleanup();
    std::cout << "SERVER_RECEIVER::SERVER_ENDED" << std::endl;
};


//////////////////////////////////////
// PHASE 4 Receiving 8080
//////////////////////////////////////
void NetworkServerUDP::server_mainloop()
{
    // ######################################################################################
    // Start Client Handle
    // ######################################################################################
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
        sockaddr_in clientSenderAddress;
        int client_addr_len = sizeof(serverReceiverAddress);
        char buffer[1024];
        int bytesRecv = recvfrom( serverReceiverSocket, buffer, sizeof(buffer), 0, (sockaddr*)&clientSenderAddress, &client_addr_len);

        if(bytesRecv <= 0)
            continue;

        std::string message(buffer, bytesRecv);
        
        std::thread(&NetworkServerUDP::clientHandle, this, message, clientSenderAddress).detach();
    }
};

void NetworkServerUDP::clientHandle(std::string buffer, sockaddr_in clientSenderAddress)
{   

    // 2. Reading Message
    std::string data = buffer;
    std::stringstream ss(data);
    
    std::string player = "0";
    std::string player_action = "0";

    std::getline(ss, player, ',');
    std::getline(ss, player_action, ',');

    // 3. Executing Message
    if(player=="1")
    {
        if(player_action=="1"){player_1_cameraPosition += glm::vec3( 0.0f , 0.0f,-0.5f);} // W
        if(player_action=="2"){player_1_cameraPosition += glm::vec3( 0.0f , 0.0f, 0.5f);} // S
        if(player_action=="3"){player_1_cameraPosition += glm::vec3(-0.5f, 0.0f, 0.0f);} // A
        if(player_action=="4"){player_1_cameraPosition += glm::vec3( 0.5f, 0.0f, 0.0f);} // D
        if(player_action=="5"){player_1_cameraPosition += glm::vec3( 0.0f, 0.5f, 0.0f);} // A
        if(player_action=="6"){player_1_cameraPosition += glm::vec3( 0.0f,-0.5f, 0.0f);} // D
    }

    if(player=="2")
    {
        if(player_action=="1"){player_2_cameraPosition += glm::vec3( 0.0f , 0.0f,-0.5f);} // W
        if(player_action=="2"){player_2_cameraPosition += glm::vec3( 0.0f , 0.0f, 0.5f);} // S
        if(player_action=="3"){player_2_cameraPosition += glm::vec3(-0.5f, 0.0f, 0.0f);} // A
        if(player_action=="4"){player_2_cameraPosition += glm::vec3( 0.5f, 0.0f, 0.0f);} // D
        if(player_action=="5"){player_2_cameraPosition += glm::vec3( 0.0f, 0.5f, 0.0f);} // A
        if(player_action=="6"){player_2_cameraPosition += glm::vec3( 0.0f,-0.5f, 0.0f);} // D
    }

    //////////////////////////////////////
    // PHASE 5 Send to 8081 Server
    //////////////////////////////////////

    // 4. Gather Data
    std::string sendData;
    sendData = std::to_string(player_1_cameraPosition.x) + ',' + std::to_string(player_1_cameraPosition.y) + ',' + std::to_string(player_1_cameraPosition.z) + ',' + std::to_string(player_2_cameraPosition.x) + ',' + std::to_string(player_2_cameraPosition.y) + ',' + std::to_string(player_2_cameraPosition.z);
    const char* message = sendData.c_str();

    // 5. Send Data
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &clientSenderAddress.sin_addr, ipstr, INET_ADDRSTRLEN );
    const char* HOST_IP = ipstr;

    sockaddr_in clientAddress;
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(8081);
    clientAddress.sin_addr.s_addr = inet_addr(HOST_IP);

    int message_len = (int)strlen(message);
    int client_addr_len = sizeof(clientAddress);

    int result = sendto(serverSenderSocket, message, message_len, 0, (sockaddr*)&clientAddress, client_addr_len);
    if (result == SOCKET_ERROR)
    {
        std::cerr << "SERVER_SENDER::ERROR::SEND_FAILED" << std::endl;
        std::cerr << WSAGetLastError() << std::endl;
        return;
    }
};