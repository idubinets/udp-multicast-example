#include "program.h"

#include <Winsock2.h> 
#include <Ws2tcpip.h>
#include <stdio.h>

#define MSG_SIZE 256

int main(int argc, char* argv[], char* envp[])
{
    char* group = argc > 1 ? argv[1] : "239.255.255.250";  // default is SSDP address: 
                                                           // https://en.wikipedia.org/wiki/Simple_Service_Discovery_Protocol
    int port = argc > 2 ? atoi(argv[2]) : 35001;

    puts("Console app for UDP multicast demostration. Command line auruments: group and port");
    printf_s("ex: receiver %s %d\r\n", group, port);

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
        perror("socket initialization failed");
        return 1;
    }

    // set up local bind address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    // allow multiple sockets to use the same port for receiving the messages
    // it is useful if you run multiple copies of your app on the same PC
    BOOL bEnable = 1;
    if (setsockopt(dgramSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&bEnable, sizeof(bEnable)) < 0) 
    {
        perror("setsockopt with SO_REUSEADDR failed");
        return 1;
    }

    // bind socket to the local address
    if (bind(dgramSocket, (struct sockaddr*) & addr, sizeof(addr)) < 0) 
    {
        perror("bind failed");
        return 1;
    }

    // join socket to multicast group using setsockopt
    struct ip_mreq mreq;
    InetPton(AF_INET, group, &mreq.imr_multiaddr.s_addr);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(dgramSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) < 0) 
    {
        perror("join socket to multicast group failed");
        return 1;
    }

    // receiver loop
    char msgbuf[MSG_SIZE];
    while (1) 
    {
        printf("Waiting for the next message: ");
        memset(msgbuf, 0, MSG_SIZE);

        int addrlen = sizeof(addr);
        int nbytes = recvfrom(
            dgramSocket,
            msgbuf,
            MSG_SIZE,
            0,
            (struct sockaddr*) & addr,
            &addrlen
        );

        if (nbytes < 0) 
        {
            perror("recvfrom failed");
            return 1;
        }

        puts(msgbuf);
    }

    // terminate use of the Winsock 2 DLL
    WSACleanup();

    return 0;
}