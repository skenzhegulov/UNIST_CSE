#include "myheader.h"

//struct for arguments to pass required info 
//to functions called in pthreads
struct args {
	struct sockaddr_in server;
	int socket;
	int npkts;
	int arr_rate;
};
//function to calculate random exponential distribution according to mean
double exp_dis(int mean) {
	return -log(1.0-((double)rand())/((double)RAND_MAX+1.0))/mean;
}
//function which generates and sends packets to the server
void* send(void* ptr) {
	struct args* info = (struct args*)ptr;
	myFrame curr;
	int n;
	//get all info to send to server
	int npkts = info->npkts;
	int s = info->socket;
	int arr_rate = info->arr_rate;
	struct sockaddr_in addr = info->server;
	double temp;
	struct timespec waitTime;
	struct timespec txTime;
	//generate nkpts
	for(int i=0; i<npkts; i++) {
		memset(&curr, 0, sizeof(curr));
		curr.dataByte = MAXQLEN+1;
		//saving seqno
		curr.seqno = i;
		//generating packet size
		curr.dataByte = (int)(exp_dis(1)*1000)%MAXQLEN+1;
		//generating arrival time
		temp = exp_dis(arr_rate);
		waitTime.tv_sec = (int)temp;
		waitTime.tv_nsec = (int)((temp-(int)temp)*1E9);
		//simulating arrival time
		nanosleep(&waitTime, NULL);
		//getting realtime
		clock_gettime(CLOCK_REALTIME, &curr.clientTxTime);
		//printing all info
		printf("%u.%09u\tTX %d size %d\n", curr.clientTxTime.tv_sec, curr.clientTxTime.tv_nsec, curr.seqno, curr.dataByte);
		//send packet to the server
		n = sendto(s, (char*)&curr, sizeof(myFrame), 0, (struct sockaddr *)&addr, sizeof(addr));
		if(n<0) {
			perror("Error:\n");
			pthread_exit(NULL);
			return NULL;
		}
	}
	//send one more packet so server know previous was the last
	curr.seqno = -1;
	n = sendto(s, (char*)&curr, sizeof(myFrame), 0, (struct sockaddr *)&addr, sizeof(addr));
	if(n<0) {
		perror("Error:\n");
	}
	pthread_exit(NULL);
	return NULL;
}
//function to receive packets from server
void* receive(void* ptr) {
	struct args* info = (struct args*)ptr;
	int npkts = info->npkts;
	int s = info->socket;
	struct sockaddr_in addr = info->server;
	myFrame curr;
	int n;
	int addr_len;
	struct timespec rxTime;
	//loop to receive packets
	while(1) {
		memset(&curr, 0, sizeof(curr));
		addr_len = sizeof(addr);
		n = recvfrom(s, (char*)&curr, sizeof(myFrame), 0, (struct sockaddr*)&addr, (socklen_t*)&addr_len);
		//after receiving a packet, get current time
		clock_gettime(CLOCK_REALTIME, &rxTime);
		//print out all data
		printf("%u.%09u\tRX %d size %d    \tqlen %d delay %u.%09u\n", rxTime.tv_sec, rxTime.tv_nsec, curr.seqno, curr.dataByte, curr.serverQueueLen, rxTime.tv_sec-curr.clientTxTime.tv_sec, rxTime.tv_nsec-curr.clientTxTime.tv_nsec);
		//if it was the last packet, finish the loop
		if(curr.seqno==npkts-1) break;
	}
	pthread_exit(NULL);
	return NULL;
}

int main(int argc, char* argv[]) 
{
	srand(time(0));
	int s;
	char* servName;
	int servPort;
	int len = 0;
	struct sockaddr_in serverAddr;
	int n;
	int npkts = 0;
	int arr_rate;
	struct timespec txTime;
	struct timespec rxTime;

	myFrame txData;
	myFrame rxData;

	if(argc != 5)
	{
		printf("Usage: echoClient <server IP> <port> <arrival_rate> <npkts>\n");
		exit(1);
	}

	servName = argv[1];
	servPort = atoi(argv[2]);
	arr_rate = atoi(argv[3]);
	npkts = atoi(argv[4]);

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

	struct args info;
	info.socket = s;
	info.server = serverAddr;
	info.npkts = npkts;
	info.arr_rate = arr_rate;
	//create pthreads
	pthread_t thread1, thread2;
	//run send function on thread1
	if(pthread_create(&thread1, NULL, &send, (void*)&info)) {
		printf("Thread 1 error\n");
		return -1;
	}
	//run receive function on thread2
	if(pthread_create(&thread2, NULL, &receive, (void*)&info)) {
		printf("Thread 2 error\n");
		return -1;
	}
	//wait until threads finishes
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	close(s);
	exit(0);
}
