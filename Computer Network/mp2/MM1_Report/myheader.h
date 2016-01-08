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
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <pthread.h>
#include <math.h>
#include <algorithm>

#define MAXQLEN 65535

struct myFrame
{
	int seqno;
	struct timespec clientTxTime;
	unsigned int dataByte;
	int serverQueueLen;
};


#endif
