#ifndef UDP_H
#define UDP_H

#include <netinet/in.h>

void diep(char *s);
void udp_init (void);
void udp_send (volatile unsigned char udp_cube[8][8]);

struct sockaddr_in si_other;
int udp_socket, slen;

#endif

