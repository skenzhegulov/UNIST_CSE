#include "myheader.h"

int main(int argc, char* argv[]) 
{
	int s;
	char* servName;
	int servPort;
	Frame msg;
	int len = 0;
	int maxLen = sizeof(msg);
	struct sockaddr_in serverAddr;
	int n;

	if(argc != 5)
	{
		printf("Usage: client <server IP> <server port> <pkt_size> <string>\n");
		exit(1);
	}
	//get server IP, Port, packet size, string values
	servName = argv[1];
	servPort = atoi(argv[2]);

	/* Create remote (server) socket address */
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, servName, &serverAddr.sin_addr);	// server IP addr
	serverAddr.sin_port = htons(servPort);

	/* Creat socket */
	if((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Error: socket creation failed\n");
		exit(1);
	}

	//obtain the current client time and construct frame client time
	if( clock_gettime( CLOCK_REALTIME, &msg.client_t) == -1 ) {
	      printf( "clock gettime\n" );
	      exit(1);
	}
	
	//print current client time
	printf("TX at %lld.%.9ld\n", (long long)msg.client_t.tv_sec, msg.client_t.tv_nsec);
	
	//construct frame's additional info
	msg.pkt_size = atoi(argv[3]);
	msg.seqno = 0;
	char *string = argv[4];
	n = strlen(string);
	strncpy(msg.string, string, n);
	msg.string[n] = '\0';
	
	// send the frame
	n = sendto(s, &msg, sizeof(msg), 0,
		(struct sockaddr *)&serverAddr, sizeof(serverAddr));

	// wait for the echoed frame
	len = recvfrom(s, &msg, sizeof(msg), 0, NULL, NULL);
	
	//print echoed frame server time and string
	printf("RX at %lld.%.9ld\n", (long long)msg.server_t.tv_sec, msg.server_t.tv_nsec);
	printf("String: %s\n", msg.string);
	
	close(s);
	exit(0);
}
