#include "myheader.h"

//queue structure
struct queue 
{
	bool used; //checks if queue in use or not, for pthreads
	int front; //queue's first item's pointer
	int back;  //queue's last item's pointer
	int buff_s;//buffer size
	struct sockaddr_in Addr[MAXQLEN]; //array to store client's address
	myFrame q[MAXQLEN];		  //array of packet frames
	//constructor
	queue() : front(0), back(0), used(false) {
		memset(q, 0, sizeof(q));
		memset(Addr, 0, sizeof(Addr));
	}
	//set buffer size
	void set_buff(int buff) {
		buff_s = buff;
	}
	//check whether buffer is full or not
	bool isFull() {
		if(back-front>=buff_s) return true;
		return false;
	}
	//check for emtiness of the queue
	bool isEmpty() {
		if(front==back) return true;
		return false;
	}
	//get curre queue length
	int size() {
		return back-front;
	}
	//enqueue packet to the queue if buffer is not full
	bool enq(myFrame elem, struct sockaddr_in addr) {
		if(isFull()) return false;
		elem.serverQueueLen = size();
		q[back] = elem;
		Addr[back] = addr;
		back = back+1;
		return true;
	}
	//get first packet from queue of there exist
	bool deq(myFrame &elem, struct sockaddr_in &addr) {
		if(isEmpty()) return false;
		elem = q[front];
		addr = Addr[front];
		//front = front+1;
		return true;
	}
} Q;

//function to proceed packets
void* service(void* ptr) {
	int *s;
	s = (int*)ptr;
	int ls = *s;
	struct timespec sleepTime;
	struct timespec currTime;
	struct sockaddr_in addr;
	double temp;
	int n;
	//bandwidth 1000Kbps = 1000*1000/8 = 125000Bps 
	int bandwidth = 125000;
	myFrame curr;
	//loop while queue is not empty
	while(!Q.isEmpty()) {
		memset(&curr, 0, sizeof(curr));
		//if deque succeed then serve packet
		if(Q.deq(curr, addr)) {
			//calculate service time
			temp = (1.0*curr.dataByte)/(1.0*bandwidth);
			sleepTime.tv_sec = (int)temp;
			sleepTime.tv_nsec = (int)((temp-(int)temp)*1E9);
			//imitate delay for service
			nanosleep(&sleepTime, NULL);
			//get time current time and send it back to client
			clock_gettime(CLOCK_REALTIME, &currTime);
			n = sendto(ls, (char*)&curr, sizeof(myFrame), 0, (struct sockaddr*)&addr, sizeof(addr));
			if (n<0) {
				perror("Error:\n");
				exit(1);
			}
			//if everything ok print out info
			printf("%u.%09u\t%d\t- pkt %d size %d  \tserv time %.9lf\n", currTime.tv_sec, currTime.tv_nsec, Q.size(), curr.seqno, curr.dataByte, temp);
			//move to the next packet in queue
			Q.front = Q.front+1;
		}
	}
	//indicate that queue is no longer in use
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
	int bufferspace;

	if(argc != 3)
	{
		printf("Usage: echoServer <port(10000~30000)> <bufferspace(1~65535)>\n");
		exit(1);
	}
	
	servPort = atoi(argv[1]);
	bufferspace = atoi(argv[2]);

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
	//set buffer space
	Q.set_buff(bufferspace);
	//start receiving packets
	while(1)
	{
		memset(&rxData, 0, sizeof(rxData));
		clientAddrLen = sizeof(clientAddr);
		len = recvfrom(ls, (char*)&rxData, sizeof(myFrame), 0,
			(struct sockaddr*) &clientAddr, (socklen_t *) &clientAddrLen);
		//check for the end of packet transfer
		if(rxData.seqno==-1) break;
		//get current time
		clock_gettime(CLOCK_REALTIME, &rxTime);
		//print out info
		if(Q.enq(rxData, clientAddr)) {
				//print + if enqueue was successful
				printf("%u.%09u\t%d\t+ pkt %d\n", rxTime.tv_sec, rxTime.tv_nsec, rxData.serverQueueLen, rxData.seqno); 
			} else  
				//print x if failed
				printf("%u.%09u\t%d\tx pkt %d\n", rxTime.tv_sec, rxTime.tv_nsec, Q.size(), rxData.seqno); 
		//if queue is not empty and not in use, call child thread for service
		if(!Q.isEmpty() && !Q.used) {
			Q.used = true;
			if (pthread_create(&thread, NULL, service, (void*) &ls)) {
				fprintf(stderr, "Error - pthread_create()\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	//wait until phtread finishes its work
	pthread_join(thread, NULL);
	close(ls);
	exit(0);
}
