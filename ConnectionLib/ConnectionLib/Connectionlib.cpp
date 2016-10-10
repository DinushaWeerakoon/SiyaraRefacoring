#include "Connectionlib.h"
#include <winsock2.h>
#include <stdio.h>
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

	static void init(){

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
			// Do the clean up
			WSACleanup();
			// Exit with error
			//return -1;
		}

	}

	// send data
	static char* SendData(char name[], int mmsi, double lat, double lon){
		//sendbuf = '{ "name":"'+John Johnson'", "mmsi" : "'+Oslo West 16+'", "lat" : "'+555 1234567+'", "lon" : "'+555 1234567+'" }';
		char sendbuf[1024] = "This is a test string from sender";
		BytesSent = send(SendingSocket, sendbuf, strlen(sendbuf), 0);

		/*if (BytesSent == SOCKET_ERROR)
			printf("Client: send() error %ld.\n", WSAGetLastError());
		else
		{
			printf("Client: send() is OK - bytes sent: %ld\n", BytesSent);
			// Some info on this sender side...
			// Allocate the required resources
			memset(&ThisSenderInfo, 0, sizeof(ThisSenderInfo));
			nlen = sizeof(ThisSenderInfo);

			getsockname(SendingSocket, (SOCKADDR *)&ThisSenderInfo, &nlen);
			printf("Client: Sender IP(s) used: %s\n", inet_ntoa(ThisSenderInfo.sin_addr));
			printf("Client: Sender port used: %d\n", htons(ThisSenderInfo.sin_port));
			printf("Client: Those bytes represent: \"%s\"\n", sendbuf);
		}*/
	}
}