#include <iostream>
#include <bitset>
#include <stdio.h>
#include<stdlib.h>
#include <string>
using namespace std;

#define L1_CACHE_SETS 64
#define L2_CACHE_SETS 64
#define VICTIM_SIZE 16
#define L2_CACHE_WAYS 8
#define MEM_SIZE 4096
#define BLOCK_SIZE 4 // bytes per block
#define DM 0
#define SA 1

struct cacheBlock
{
	int tag; // you need to compute offset and index to find the tag.
	int lru_position; // for SA only
	int data; // the actual data stored in the cache/memory
	bool valid;
	// add more things here if needed
};

struct Stat
{

	int missL1; 
	int missL2; 
	int accL1;
	int accL2;
	int missVI;
	int accVI;
	
	// add more stat if needed. Don't forget to initialize!
};

class cache {
private:
	cacheBlock L1[L1_CACHE_SETS]; // 1 set per row.
	cacheBlock L2[L2_CACHE_SETS][L2_CACHE_WAYS]; // x ways per row 
	// Add your Victim cache here ...
	cacheBlock VICTIM[VICTIM_SIZE];
	//int MEMORY[MEM_SIZE]; //already defined in memory_driver

	Stat myStat;
	// add more things here
public:
	cache();
	void controller(bool MemR, bool MemW, int* data, int adr, int* myMem);
	double returnMissL1();
	double returnMissL2();
	double returnAccL1();
	double returnAccL2();
	double returnMissVI();
	double returnAccVI();
	// add more functions here ...	
	
};


