#include "program.h"

#include <Winsock2.h> 
#include <Ws2tcpip.h>
#include <stdio.h>

#define MSG_SIZE 256

int main(int argc, char *argv[], char *envp[])
{
    char* group = argc > 1 ? argv[1] : "239.255.255.250";  // default is SSDP address: https://en.wikipedia.org/wiki/Simple_Service_Discovery_Protocol
    int port = argc > 2 ? atoi(argv[2]) : 35001;

    puts("Console app for UDP multicast demostration. Command line auruments: group and port");
    printf_s("ex: sender %s %d\r\n", group, port);
   
    // init Winsock DLL
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        perror("Winsock DLL initialization failed");
        return 1;
    }

    // create datagram socket
    SOCKET dgramSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO::IPPROTO_UDP);
    if (dgramSocket == INVALID_SOCKET) 
    {
        perror("socket");
        return 1;
    }

    // set up destination address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    InetPton(AF_INET, group, &addr.sin_addr.s_addr);
    addr.sin_port = htons(port);

    // main sender loop
    char msgbuf[MSG_SIZE];
    while (1) 
    {
        memset(msgbuf, 0, MSG_SIZE);
        puts("Type a message to send: ");
        gets_s(msgbuf, MSG_SIZE);
        size_t msgLen = strlen(msgbuf);

        if (msgLen <= 0) 
        {
            puts("The message you typed is empty");
            continue;
        }

        int nbytes = sendto(
            dgramSocket,
            msgbuf,
            (int) msgLen,
            0,
            (struct sockaddr*) & addr,
            sizeof(addr)
        );
         
        if (nbytes < 0) 
        {
            perror("sendto failed");
            return 1;
        }
    }

    // terminate use of the Winsock 2 DLL
    WSACleanup();

    return 0;
}