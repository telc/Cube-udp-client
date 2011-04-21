#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "udp.h"

#define BUFLEN 64
#define PORT 9930
#define SERVER_IP "188.0.86.152"

void diep(char *s)
{
    perror(s);
    exit(1);
}

void udp_init (void)
{
    slen=sizeof(struct sockaddr);

    if ((udp_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        diep("socker error, oh noes!!");

    memset((char *) &si_other, 0, sizeof(struct sockaddr));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    if (inet_aton(SERVER_IP, &si_other.sin_addr)==0)
        diep("inet_aton erorro");

}

void udp_send (volatile unsigned char udp_cube[8][8])
{
    if(sendto(udp_socket, udp_cube, BUFLEN, 0, (struct sockaddr*) &si_other, slen)==-1)
        diep("Aiaiaia send fail omgomgom!!");
}

