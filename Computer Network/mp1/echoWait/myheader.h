#ifndef _MYHEAD_
#define _MYHEAD_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <time.h>

//structure of packet frame: seqno, client and server times, packet size, string
struct Frame {
	unsigned short seqno;
	struct timespec client_t;
	struct timespec server_t;
	unsigned short pkt_size;
	char string[81];
};

#endif
