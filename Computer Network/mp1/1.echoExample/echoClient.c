#include "myheader.h"

int main(int argc, char* argv[]) 
{
	int s;
	char* servName;
	int servPort;
	char* string;
	char buf[256 + 1];
	int len = 0;
	int maxLen = sizeof(buf);
	struct sockaddr_in serverAddr;
	int n;

	if(argc != 4)
	{
		printf("Usage: client <server> <port> <string>\n");
		exit(1);
	}

	servName = argv[1];
	servPort = atoi(argv[2]);
	string = argv[3];

	memset(&buf, 0, sizeof(buf));

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

	// send the echo message
	n = sendto(s, string, strlen(string), 0,
		(struct sockaddr *)&serverAddr, sizeof(serverAddr));
	printf("string sent (%d bytes)\n",n);

	/* here, the message has been sent, and the echo will come */

	/* receive Echo */
	memset(&buf, 0, sizeof(buf));
	len = recvfrom(s, buf, sizeof(buf), 0, NULL, NULL);
	buf[len] = '\0';

	printf("Echoed string received: ");
	printf("%s\n", buf);

	close(s);
	exit(0);
}
