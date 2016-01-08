#include "myheader.h"

struct args {
	struct sockaddr_in server;
	int socket;
	int npkts;
	int arr_rate;
};

int total_pkts = 0;
double delays[1000];

double exp_dis(int mean) {
	return -log(1.0-((double)rand())/((double)RAND_MAX+1.0))/mean;
}

void* send(void* ptr) {
	struct args* info = (struct args*)ptr;
	myFrame curr;
	int n;
	int npkts = info->npkts;
	int s = info->socket;
	int arr_rate = info->arr_rate;
	struct sockaddr_in addr = info->server;
	double temp;
	struct timespec waitTime;
	struct timespec txTime;
	for(int i=0; i<npkts; i++) {
		memset(&curr, 0, sizeof(curr));
		curr.dataByte = MAXQLEN+1;
		curr.seqno = i;
		curr.dataByte = ((int)(exp_dis(1)*1000))%MAXQLEN+1;
		temp = exp_dis(arr_rate);
		waitTime.tv_sec = (int)temp;
		waitTime.tv_nsec = (int)((temp-(int)temp)*1E9);
		nanosleep(&waitTime, NULL);
		clock_gettime(CLOCK_REALTIME, &curr.clientTxTime);
		printf("%u.%09u\tTX %d size %d\n", curr.clientTxTime.tv_sec, curr.clientTxTime.tv_nsec, curr.seqno, curr.dataByte);
		n = sendto(s, (char*)&curr, sizeof(myFrame), 0, (struct sockaddr *)&addr, sizeof(addr));
		if(n<0) {
			perror("Error:\n");
			pthread_exit(NULL);
			return NULL;
		}
	}
	curr.seqno = -1;
	n = sendto(s, (char*)&curr, sizeof(myFrame), 0, (struct sockaddr *)&addr, sizeof(addr));
	if(n<0) {
		perror("Error:\n");
		pthread_exit(NULL);
		return NULL;
	}
}

void* receive(void* ptr) {
	struct args* info = (struct args*)ptr;
	int npkts = info->npkts;
	int s = info->socket;
	struct sockaddr_in addr = info->server;
	myFrame curr;
	int n;
	int addr_len;
	struct timespec rxTime;
	double delay;
	while(1) {
		memset(&curr, 0, sizeof(curr));
		addr_len = sizeof(addr);
		n = recvfrom(s, (char*)&curr, sizeof(myFrame), 0, (struct sockaddr*)&addr, (socklen_t*)&addr_len);
		clock_gettime(CLOCK_REALTIME, &rxTime);
		delay = (double)rxTime.tv_sec-curr.clientTxTime.tv_sec + (double)(rxTime.tv_nsec-curr.clientTxTime.tv_nsec)/1e9;
		delays[curr.seqno] = delay;
		printf("%u.%09u\tRX %d size %d  \tqlen %d delay %.9lf\n", rxTime.tv_sec, rxTime.tv_nsec, curr.seqno, curr.dataByte, curr.serverQueueLen, delay);
		total_pkts += curr.serverQueueLen;
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
	double rho;	
	FILE *f1 = fopen("data1.txt", "w");
	FILE *f2 = fopen("data2.txt", "w");
	pthread_t thread1, thread2;
	int arrs[11] = {30, 50, 70, 90, 110, 115, 120, 121, 122, 123, 124};
	for(int i=0; i<11; i++) {
		info.arr_rate = arrs[i];
		if(pthread_create(&thread1, NULL, &send, (void*)&info)) {
			printf("Thread 1 error\n");
			return -1;
		}
		if(pthread_create(&thread2, NULL, &receive, (void*)&info)) {
			printf("Thread 2 error\n");
			return -1;
		}

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		rho = (1.0*arrs[i])/125.0;
		fprintf(f1, "%d => \t%lf\t%lf\n", arrs[i], rho, (double)(total_pkts/npkts));
		if(arrs[i]==120) {
			std::sort(delays, delays+npkts);
			for(int j=0; j<npkts; j++) fprintf(f2, "\t%d  %.9lf\n", j, delays[j]);
		}
	}
	fclose(f1);
	fclose(f2);
	info.arr_rate = 120;
	if(pthread_create(&thread1, NULL, &send, (void*)&info)) {
		printf("Thread 1 error\n");
		return -1;
	}
	if(pthread_create(&thread2, NULL, &receive, (void*)&info)) {
		printf("Thread 2 error\n");
		return -1;
	}
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	FILE *f3 = fopen("data3.txt","w");
	std::sort(delays, delays+npkts);
	for(int j=0; j<npkts; j++) fprintf(f3, "\t%d  %.9lf\n", j, delays[j]);

	fclose(f3);
	close(s);
	exit(0);
}
