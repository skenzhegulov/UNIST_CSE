#include "myheader.h"

struct queue 
{
	bool used;
	int front;
	int back;
	int buff_s;
	struct sockaddr_in Addr[MAXQLEN];
	myFrame q[MAXQLEN];
	
	queue() : front(0), back(0), used(false) {
		memset(q, 0, sizeof(q));
		memset(Addr, 0, sizeof(Addr));
	}
	
	void set_buff(int buff) {
		buff_s = buff;
	}

	bool isFull() {
		if(back-front>=buff_s) return true;
		return false;
	}
	
	bool isEmpty() {
		if(front==back) return true;
		return false;
	}
	
	int size() {
		return back-front;
	}
	
	bool enq(myFrame elem, struct sockaddr_in addr) {
		if(isFull()) return false;
		elem.serverQueueLen = size();
		q[back] = elem;
		Addr[back] = addr;
		back = back+1;
		return true;
	}
	
	bool deq(myFrame &elem, struct sockaddr_in &addr) {
		if(isEmpty()) return false;
		elem = q[front];
		addr = Addr[front];
		//front = front+1;
		return true;
	}
} Q;

void* service(void* ptr) {
	int *s;
	s = (int*)ptr;
	int ls = *s;
	//printf("Thread started with socket %d\n", ls);
	struct timespec sleepTime;
	struct timespec currTime;
	struct sockaddr_in addr;
	double temp;
	int n;
	int bandwidth = 125000;
	myFrame curr;
	while(!Q.isEmpty()) {
		memset(&curr, 0, sizeof(curr));
		if(Q.deq(curr, addr)) {
			temp = (1.0*curr.dataByte)/(1.0*bandwidth);
			sleepTime.tv_sec = (int)temp;
			sleepTime.tv_nsec = (int)((temp-(int)temp)*1E9);
			nanosleep(&sleepTime, NULL);
			clock_gettime(CLOCK_REALTIME, &currTime);
			n = sendto(ls, (char*)&curr, sizeof(myFrame), 0, (struct sockaddr*)&addr, sizeof(addr));
			if (n<0) {
				perror("Error:\n");
				exit(1);
			}
			printf("%u.%09u\t%d\t- pkt %d size %d  \tserv time %.9lf\n", currTime.tv_sec, currTime.tv_nsec, Q.size(), curr.seqno, curr.dataByte, temp);
			Q.front = Q.front+1;
		}
	}
	Q.used = false;
	pthread_exit(NULL);
	return NULL;
}

int main(int argc, char* argv[]) 
{
	int ls;
	char* string;
	int len = 0;
	int waitSize = 16;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	int clientAddrLen;
	int servPort;
	int n;
	int bandwidth;
	int bufferspace;

	if(argc != 3)
	{
		printf("Usage: echoServer <port(10000~30000)> <bufferspace(1~65535)>\n");
		exit(1);
	}
	
	servPort = atoi(argv[1]);
	bufferspace = atoi(argv[2]);
	//bandwidth => 1000Kbps => 1000*1000/8 => 125000Bps
	bandwidth = 125000;

	if(servPort < 10000 || servPort > 30000 ||
		bufferspace < 1 || bufferspace > 65535 ) 
	{
		printf("Usage: server <port(10000~30000)> <bufferspace(1~65535)>\n");
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
	//printf("Socket is => %d\n", ls);
	myFrame rxData;
	pthread_t thread;


	
	struct timespec rxTime;
	struct timespec txTime;
	struct timespec sleepTime;
	double temp;

	Q.set_buff(bufferspace);
for(int i=0; i<11; i++) {
	while(1)
	{
		memset(&rxData, 0, sizeof(rxData));

		/* send Echo */
		clientAddrLen = sizeof(clientAddr);
		len = recvfrom(ls, (char*)&rxData, sizeof(myFrame), 0,
			(struct sockaddr*) &clientAddr, (socklen_t *) &clientAddrLen);
		if(rxData.seqno==-1) break;
		clock_gettime(CLOCK_REALTIME, &rxTime);
		//rxData.serverQueueLen = Q.size();
		if(Q.enq(rxData, clientAddr)) {
				printf("%u.%09u\t%d\t+ pkt %d\n", rxTime.tv_sec, rxTime.tv_nsec, rxData.serverQueueLen, rxData.seqno); 
			} else  
				printf("%u.%09u\t%d\tx pkt %d\n", rxTime.tv_sec, rxTime.tv_nsec, Q.size(), rxData.seqno); 
		if(!Q.isEmpty() && !Q.used) {
			Q.used = true;
			if (pthread_create(&thread, NULL, service, (void*) &ls)) {
				fprintf(stderr, "Error - pthread_create()\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	
	pthread_join(thread, NULL);
}
	Q.set_buff(50);
	while(1)
	{
		memset(&rxData, 0, sizeof(rxData));

		/* send Echo */
		clientAddrLen = sizeof(clientAddr);
		len = recvfrom(ls, (char*)&rxData, sizeof(myFrame), 0,
			(struct sockaddr*) &clientAddr, (socklen_t *) &clientAddrLen);
		if(rxData.seqno==-1) break;
		clock_gettime(CLOCK_REALTIME, &rxTime);
		//rxData.serverQueueLen = Q.size();
		if(Q.enq(rxData, clientAddr)) {
				printf("%u.%09u\t%d\t+ pkt %d\n", rxTime.tv_sec, rxTime.tv_nsec, rxData.serverQueueLen, rxData.seqno); 
			} else  
				printf("%u.%09u\t%d\tx pkt %d\n", rxTime.tv_sec, rxTime.tv_nsec, Q.size(), rxData.seqno); 
		if(!Q.isEmpty() && !Q.used) {
			Q.used = true;
			if (pthread_create(&thread, NULL, service, (void*) &ls)) {
				fprintf(stderr, "Error - pthread_create()\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	
	pthread_join(thread, NULL);
	close(ls);
	exit(0);
}
