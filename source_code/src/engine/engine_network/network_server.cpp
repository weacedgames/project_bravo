#include "network_server.h"

NetworkServer::NetworkServer()
{
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        SERVER_MESSAGES.push_back("ERROR::WSA_STARTUP_FAILED");
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocket == -1)
    {
        WSACleanup();
        SERVER_MESSAGES.push_back("ERROR::FAILED_TO_CREATE_SOCKET");
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    if( bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR )
    {
        closesocket(serverSocket);
        WSACleanup();
        SERVER_MESSAGES.push_back("ERROR::FAILED_TO_BIND, Code: " + std::to_string(WSAGetLastError()));
    }
    
    if(listen(serverSocket, 5) == SOCKET_ERROR)
    {
        SERVER_MESSAGES.push_back("ERROR::FAILED_TO_LISTEN, Code: " + std::to_string(WSAGetLastError()));
        closesocket(serverSocket);
        WSACleanup();
    }

    SERVER_MESSAGES.push_back("SERVER::SERVER_STARTED");
    SERVER_MESSAGES.push_back("SERVER::AWAITING_CONNECTIONS");

    std::thread thread_run(&NetworkServer::run,this,serverSocket);
    thread_run.detach();
};

void NetworkServer::run(SOCKET serverSocket)
{
    // ######################################################################################
    // Start Client Handle
    // ######################################################################################

    sockaddr_in clientAddress;
    int clientSize = sizeof(clientAddress);
    SOCKET clientSocket = accept( serverSocket, (sockaddr*)&clientAddress, &clientSize);
    SERVER_MESSAGES.push_back("CLIENT::CONNECTED");
    
    while(true){
        char buffer[1024] = {};
        recv( clientSocket, buffer, sizeof(buffer), 0);

        std::string data = buffer;
        SERVER_MESSAGES.push_back("CLIENT::" + data);

        std::stringstream ss(data);
        std::string token;

        std::string packet_type;
        int player_id = 0;
        std::string username;

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        // Data Packet Format
        // Variable Type: string,int,string,float,float,float
        // Variable Names: packet_type,player_id,username,x,y,z
        //////////////////////////////////////////////////////////////
        std::getline(ss, packet_type, ',');
        std::getline(ss, username, ',');

//        std::getline(ss, token, ',');
//        player_id = std::stoi(token);
//
//        std::getline(ss, token, ',');
//        x = std::stof(token);
//
//        std::getline(ss, token, ',');
//        y = std::stof(token);
//
//        std::getline(ss, token, ',');
//        z = std::stof(token);
        //////////////////////////////////////////////////////////////

        if(packet_type=="quit"){break;}
        if(packet_type=="move")
        {
            std::cout << "CLIENT::" << username << "::MOVED::SHIT" << std::endl;
            //updatePlayerPosition( player_id, glm::vec3(x,y,z)); 
        }

        
        // Gonna Have to rip out the majority of this crap out
        // It worked for a temp run, but to make it into something useable is another matter on its own
        // Still going to use sending position until I figure sending actions only
        // The server will be responsible for game logic
        // I think this wraps up task 38, create a client
        // I think 39 is update the server
        // Task 40 I will be making the 2 work together, I will also need to redesign map,
        // My solution is players are in the game like a spawn point, but are not render till a player join and takes over character
        // For example there will 4x players, 2x on each team
        // Starting spawn will represent where players position starts
        // In theory XD I honestly have no idea if this shit is going to work XD
        
    }

    closesocket(clientSocket);
    SERVER_MESSAGES.push_back("CLIENT::DISCONNECTED");
    
    // ######################################################################################
    // End Client Handle
    // ######################################################################################

    closesocket(serverSocket);
    WSACleanup();
    SERVER_MESSAGES.push_back("SERVER::SERVER_ENDED");
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Add
/////////////////////////////////////////////////////////////////////////////////////////////////////


void NetworkServer::addPlayer(int player_id, std::string username, glm::vec3 position)
{
    players_id.push_back(player_id);
    players_username.push_back(username);
    players_position.push_back(position);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Remove
/////////////////////////////////////////////////////////////////////////////////////////////////////


void NetworkServer::removePlayer(int player_id)
{
    players_id.erase(players_id.begin() + player_id);
    players_username.erase(players_username.begin() + player_id);
    players_position.erase(players_position.begin() + player_id);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Update
/////////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkServer::updatePlayerId(int player_id, int setId)
{
    players_id[player_id] = setId;
};

void NetworkServer::updatePlayerUsername(int player_id, std::string setUsername)
{
    players_username[player_id] = setUsername;
};

void NetworkServer::updatePlayerPosition(int player_id, glm::vec3 setPosition)
{
    players_position[player_id] = setPosition;
};



/////////////////////////////////////////////////////////////////////////////////////////////////////
// Return
/////////////////////////////////////////////////////////////////////////////////////////////////////


int NetworkServer::returnPlayerId(int player_id)
{
    return players_id[player_id];
}

glm::vec3 NetworkServer::returnPlayerPosition(int player_id)
{
    return players_position[player_id];
};

std::string NetworkServer::returnPlayerUsername(int player_id)
{
    return players_username[player_id];
};

std::vector<std::string> NetworkServer::return_server_messages()
{
    return SERVER_MESSAGES;
};
