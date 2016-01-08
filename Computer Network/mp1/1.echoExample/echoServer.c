#include "myheader.h"

int main(int argc, char* argv[]) 
{
	int ls;
	char* string;
	char buf[256];
	int len = 0;
	int waitSize = 16;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	int clientAddrLen;
	int servPort;
	int n;

	if(argc != 2)
	{
		printf("Usage: server <port(10000~30000)>\n");
		exit(1);
	}
	
	servPort = atoi(argv[1]);
	if(servPort < 10000 || servPort > 30000) 
	{
		printf("Usage: server <port(10000~30000)>\n");
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

	while(1)
	{
		memset(&buf, 0, sizeof(buf));

		/* send Echo */
		clientAddrLen = sizeof(clientAddr);
		len = recvfrom(ls, buf, sizeof(buf), 0,
			(struct sockaddr*) &clientAddr, (socklen_t *) &clientAddrLen);
		printf("Received: %s\n", buf);

		// debug: printf("%s\n",inet_ntoa(clientAddr.sin_addr));

		// send the echo message
		n = sendto(ls, buf, strlen(buf), 0,
			(struct sockaddr *)&clientAddr, sizeof(clientAddr));
		if(n < 0) {
			perror("Error:\n");
			exit(1);
		}
		printf("Echo sent (%d bytes)\n", n);

		// check sentinel
		if(strcmp(buf, ".") == 0) 
		{
			close(ls);
			break;
		}
	}

}
