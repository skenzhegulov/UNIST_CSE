#include "myheader.h"

int main(int argc, char* argv[]) 
{
	int ls;
	int len = 0;
	int waitSize = 16;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	int clientAddrLen;
	int servPort;
	int fixDelay;
	int bandWidth;
	int n;
	Frame msg;

	if(argc != 4)
	{
		printf("Usage: server <port(10000~30000)> <fixed delay(1~1000ms)> <bandwidth(1~1000Kbps)>\n");
		exit(1);
	}
	//get server port, fixed delay, bandwidth values
	servPort = atoi(argv[1]);
	fixDelay = atoi(argv[2]);
	bandWidth = atoi(argv[3]);

	if(servPort < 10000 || servPort > 30000 || fixDelay < 1 || fixDelay > 1000 || bandWidth < 1 || bandWidth > 1000) 
	{
		printf("Usage: server <port(10000~30000)> <fixed delay(1~1000ms)> <bandwidth(1~1000Kbps)>\n");
		exit(1);
	}

	/* Create local (server) socket address */
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// default IP addr
	serverAddr.sin_port = htons(servPort);


	/* Creat listen socket */
	if((ls = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Error: listen socket failed\n");
		exit(1);
	}

	/* Bind listen socket to the local socket address */
	if(bind(ls, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) 
	{
		perror("Error: binding failed\n");
		exit(1);
	}

	while(1) {
		/* send Echo */
		clientAddrLen = sizeof(clientAddr);
		len = recvfrom(ls, &msg, sizeof(msg), 0,
			(struct sockaddr*) &clientAddr, (socklen_t *) &clientAddrLen);	
		//print received packet frame contents
		printf("+ sent at: %lld.%.9ld / seqno: %d / size: %d / %s\n", (long long)msg.client_t.tv_sec, msg.client_t.tv_nsec, msg.seqno, msg.pkt_size, msg.string);
		//calculate delay time
		double wait =(fixDelay/1000.0+(8.0*msg.pkt_size)/(bandWidth*1000.0));
		struct timespec wait_t; 
			wait_t.tv_sec = 0;
			wait_t.tv_nsec = (long long)(wait*1000000000);		
		//wait (or sleep)
		printf("Sleep for %f second\n", wait);
		nanosleep(&wait_t, NULL);
		//obtain current server time and update received frame
		if( clock_gettime( CLOCK_REALTIME, &msg.server_t) == -1 ) {
			printf("clock gettime\n");
			exit(1);
		}
		// send back the frame
		n = sendto(ls, &msg, sizeof(msg), 0,
			(struct sockaddr *)&clientAddr, sizeof(clientAddr));
		if(n < 0) {
			perror("Error:\n");
			exit(1);
		}
		msg.string[strlen(msg.string)] = '\0';
		//print contents of sent frame
		printf("- echo at: %lld.%.9ld / seqno: %d / size: %d / %s\n", (long long)msg.server_t.tv_sec, msg.server_t.tv_nsec, msg.seqno, msg.pkt_size, msg.string);	
		// check sentinel
		if(strcmp(msg.string, ".") == 0) {
			close(ls);
			break;
		}
	}

}
