#include "Connectionlib.h"
#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <errno.h>
#include <stdio.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib") //Winsock Library
namespace ConnectionLib{
	// make a connection with tcp server
	WSADATA              wsaData;
	SOCKET               SendingSocket;
	// Server/receiver address
	SOCKADDR_IN          ServerAddr, ThisSenderInfo;
	// Server/receiver port to connect to
	unsigned int         Port = 8888;
	int  RetCode;
	// Be careful with the array bound, provide some checking mechanism...
	//char sendbuf[2048];
	int BytesSent, nlen;

	bool Lib::instanceFlag = false;
	Lib* Lib::instance = NULL;
	FILE *stream;
	errno_t err= fopen_s(&stream, "list.txt", "a");

	Lib* Lib::getInstance(){
		if (!instanceFlag){
			instance = new Lib();
			instanceFlag = true;
			return instance;
		}
	}
	int  Lib::init(){

		// Initialize Winsock version 2.2
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		// Create a new socket to make a client connection.
		// AF_INET = 2, The Internet Protocol version 4 (IPv4) address family, TCP protocol
		SendingSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (SendingSocket == INVALID_SOCKET)
		{
			// Do the clean up
			WSACleanup();
			// Exit with error
			//return -1;
		}
		

		// Set up a SOCKADDR_IN structure that will be used to connect
		// to a listening server on port 5150. For demonstration
		// purposes, let's assume our server's IP address is 127.0.0.1 or localhost

		// IPv4
		ServerAddr.sin_family = AF_INET;
		// Port no.
		ServerAddr.sin_port = htons(Port);
		// The IP address
		ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		// Make a connection to the server with socket SendingSocket.
		RetCode = connect(SendingSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
		if (RetCode != 0)
		{
			// Close the socket
			closesocket(SendingSocket);
			fprintf_s(stream, "%s\n", "socket closed error in connection");
			// Do the clean up
			WSACleanup();
			// Exit with error
			//return -1;
		}
		else{
			fprintf_s(stream, "%s\n", "socket connected");
		}
		return RetCode;
	}

	// send data
	//pTargetData->MMSI, pTargetData->ShipName, pTargetData->Lon, pTargetData->Lat, pTargetData->ROTAIS, pTargetData->SOG, pTargetData->COG, pTargetData->Destination
	int Lib::SendData(char name[], int mmsi, double lon, double lat){
	//int Lib::SendData(char name[], int mmsi, double lon, double lat, int rot, double sog, double cog, char dest[]){
		
		
		
		char sendbuf[1024] = "Successfully";
		std::string na = name;
		std::string mm = to_string(mmsi);
		std::string la = to_string(lat);
		std::string lo = to_string(lon);
		/*std::string de = dest;
		std::string ro = to_string(rot);
		std::string so = to_string(sog);
		std::string co = to_string(cog);*/
		std::string jsonObject = "{ \"name\":\"" + na + "\", \"mmsi\":\"" + mm + "\"lat\" : \"" + la + "\", \"lon\" : \"" + lo + "\"}";
		//std::string jsonObject = "{ \"name\":\"" + na + "\", \"mmsi\":\"" + mm + "\"lat\" : \"" + la + "\", \"lon\" : \"" + lo + "\" , \"rot\" : \"" + ro + "\", \"sog\" : \"" + so + "\", \"cog\" : \"" + co + "\", \"destination\" : \"" + de + "\"}";
		const char* jsonObj = jsonObject.c_str();
		fprintf_s(stream, "%s", "ready to sent ");
		BytesSent = send(SendingSocket, jsonObj, strlen(jsonObj), 0);
		if (BytesSent == SOCKET_ERROR)
			fprintf_s(stream,"Client: send() error %ld.\n", WSAGetLastError());
		else
		{
			fprintf_s(stream, "%d\n", BytesSent);
		}
		fclose(stream);
		return BytesSent;
		
	}
}