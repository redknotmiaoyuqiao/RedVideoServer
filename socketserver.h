#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <unistd.h>

#define LISTEN_PORT 30000

void start_tcp_server();
