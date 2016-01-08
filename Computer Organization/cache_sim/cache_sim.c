#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum cache_block_state {
	INVALID,
	VALID
};

typedef unsigned uint;

typedef struct cache_block{
	enum cache_block_state status;
	uint tag;
	uint time;
}cache_block;

uint sets;
uint assoc;
uint block;
uint block_log2 = 0;
uint total_cache_accesses = 0;
uint total_cache_misses = 0;
uint sim_time = 0;
struct cache_block *cache;

void cache_access(char inst_type, uint addr);

void cache_access(char inst_type, uint addr){
    uint ind, Tag;
    int i, j, miss;

    for(i=0; i<block_log2; i++) addr = addr/2;
    ind = addr%sets;
    Tag = addr/sets; 

    miss = 1;

    for(i=0; i<assoc; i++) {
    	j = i*sets+ind;
	if(cache[j].status == VALID && cache[j].tag == Tag) {
		cache[j].time = sim_time;
		miss = 0;
		//printf("Hit! %u\n", addr);
		break;
	}
    }

    if(miss == 1) {
    	total_cache_misses++;
	int k = ind;
	for(i=0; i<assoc; i++) {
		j = i*sets+ind;
		if(cache[j].status == INVALID) {
			k = j;
			break;
		} else if(cache[j].time<cache[k].time) k = j;
	}
	//printf("Miss! %u placed to %d\n", addr, k);
	cache[k].status = VALID;
	cache[k].tag = Tag;
	cache[k].time = sim_time;
    }
}

int main(int argc, char** argv)
{
    if (argc != 5) {
        printf("Usage: %s <number_of_sets> <associativity> <cache_block_size> <trace_file>\n", argv[0]);
        return -1;
    }
    /*
       input parameters
       argv[1] = number of sets
       argv[2] = associativity
       argv[3] = cache block size
       argv[4] = trace file name
    */
    char inst_type = 0;
    uint addr = 0;
    sets = atoi(argv[1]);
    assoc = atoi(argv[2]);
    block = atoi(argv[3]);
    while (block >>= 1) ++block_log2;

    FILE *fp = fopen(argv[4], "r");
    if (fp == NULL){
        printf("trace file does not exist\n");
        return -1;
    }

    cache=malloc(sizeof(struct cache_block)*sets*assoc);
    int i=0;
    for(i=0;i<sets*assoc;i++){
        cache[i].time=0;
        cache[i].tag=0;
        cache[i].status=INVALID;
    }

    while (fscanf(fp, "%c 0x%x\n", &inst_type, &addr) != EOF) {
        cache_access(inst_type, addr);
        total_cache_accesses++;
	    sim_time++;
    }
    
    //float percentage;
    //percentage = (1.0*total_cache_misses)/total_cache_accesses*100;
    printf("Cache accesses = %u\n", total_cache_accesses);
    printf("Cache misses = %u\n", total_cache_misses);
    //printf("Miss percentage = %f\n", percentage);
    free(cache);
    fclose(fp);

    return 0;
}

//void cache_access(char inst_type, uint addr)
//{
//    printf("type = %c, addr = 0x%08x\n", inst_type, addr); 
//}

