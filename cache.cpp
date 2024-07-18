#include "cache.h"

cache::cache()
{
	for (int i=0; i<L1_CACHE_SETS; i++){
		L1[i].data = 0;
		L1[i].tag = 0;
		L1[i].valid = false;
		L1[i].lru_position = 0;
	} 
	for (int i=0; i<L2_CACHE_SETS; i++){
		for (int j=0; j<L2_CACHE_WAYS; j++){
			L2[i][j].data = 0; 
			L2[i][j].tag = 0; 
			L2[i][j].valid = false; 
			L2[i][j].lru_position = 0; 
		}
	}
	for (int i=0; i<VICTIM_SIZE; i++){
		VICTIM[i].data = 0;
		VICTIM[i].tag = 0;
		VICTIM[i].valid = false;
		VICTIM[i].lru_position = 0;
	}

	this->myStat.missL1 =0;
	this->myStat.missL2 =0;
	this->myStat.accL1 =0;
	this->myStat.accL2 =0;
	this->myStat.accVI =0;
	this->myStat.missVI =0;
/*	cacheBlock* array1 = L1;
    int size1 = sizeof(L1) / sizeof(int);

    cacheBlock* array2 = &L2[0][0];
    int size2 = sizeof(L2) / sizeof(int);

    uintptr_t start1 = reinterpret_cast<uintptr_t>(array1);
    uintptr_t end1 = start1 + size1 * sizeof(int);

    uintptr_t start2 = reinterpret_cast<uintptr_t>(array2);
    uintptr_t end2 = start2 + size2 * sizeof(int);

    if (!(end1 <= start2 || start1 >= end2)) {
        std::cout << "Arrays overlap." << std::endl;
    } else {
        std::cout << "Arrays do not overlap." << std::endl;
    }*/	
}
double cache::returnMissL1(){
	return myStat.missL1;
};
double cache::returnMissL2(){
	return myStat.missL2;
};
double cache::returnAccL1(){
	return myStat.accL1;
};
double cache::returnAccL2(){
	return myStat.accL2;
};
double cache::returnMissVI(){
	return myStat.missVI;
};
double cache::returnAccVI(){
	return myStat.accVI;
};


void cache::controller(bool MemR, bool MemW, int* data, int adr, int* myMem)
{
	/*cout << "\nmyMem Data: ";
	for (int i = 0; i < MEM_SIZE; i += 16) {
		cout << myMem[i] << " ";
	}
	cout << "\n";*/

	/*cout << "\nVICTIM IS CURRENTLY: ";
	for (int i = 0; i < VICTIM_SIZE; ++i) {
		cout << "\nTag: " << VICTIM[i].tag << ", Data: " << VICTIM[i].data << ", Valid: " << VICTIM[i].valid << ", LRU Position: " << VICTIM[i].lru_position;
	}*/

		/*cout << "\nL1 Cache Data: ";
		for (int i = 0; i < L1_CACHE_SETS; ++i) {
			//if (i % 4 == 0) {
				cout << L1[i].data << " ";
			//}
		}

		cout << "\nVI Cache Data: ";
		for (int i = 0; i < VICTIM_SIZE; ++i) {
			//if (i % 4 == 0) {
				cout << VICTIM[i].data << " ";
			//}
		}

		cout << "\nL2 Cache Data: ";
		for (int i = 0; i < L2_CACHE_SETS; ++i) {
			//if (i % 4 == 0) {
				cout << L2[i][0].data << " ";
			//}
		}

		cout << "\nL1 Cache Valid: ";
		for (int i = 0; i < L1_CACHE_SETS; ++i) {
			//if (i % 4 == 0) {
				cout << L1[i].valid << " ";
			//}
		}

		cout << "\nVI Cache Valid: ";
		for (int i = 0; i < VICTIM_SIZE; ++i) {
			//if (i % 4 == 0) {
				cout << VICTIM[i].valid << " ";
			//}
		}

		cout << "\nL2 Cache Valid: ";
		for (int i = 0; i < L2_CACHE_SETS; ++i) {
			//if (i % 4 == 0) {
				cout << L2[i][0].valid << " ";
			//}
		}

		cout << "\nVI Cache LRU: ";
		for (int i = 0; i < VICTIM_SIZE; ++i) {
			//if (i % 4 == 0) {
				cout << VICTIM[i].lru_position << " ";
			//}
		}

		cout << "\nL2 Cache LRU: ";
		for (int i = 0; i < L2_CACHE_SETS; ++i) {
			//if (i % 4 == 0) {
				cout << L2[i][0].lru_position << " ";
			//}
		}
		cout << "\nL1 Cache Tag: ";
		for (int i = 0; i < L1_CACHE_SETS; ++i) {
			cout << L1[i].tag << " ";
		}

		cout << "\nVI Cache Tag: ";
		for (int i = 0; i < VICTIM_SIZE; ++i) {
			cout << VICTIM[i].tag << " ";
		}

		cout << "\nL2 Cache Tag: ";
		for (int i = 0; i < L2_CACHE_SETS; ++i) {
			cout << L2[i][0].tag << " ";
		}*/
	// add your code here
	if (MemR){//handle read	
	//cout << "\nrunning a read";

		/*int tag = 0;
		int index = 0;
		//attempt 2
		//L1
		index = adr & 0b111;
		if(L1[index].valid == 1){
			

		};*/
		/*int index = adr & 0b111100;
		int tag = adr >> 6; 
		if (L1[index].tag == tag){ cout << "Read" << L1[index].data << "from L1. Address was" << adr; }//nobody wrote to the tag so even if the valid flag was cared about, it wouldnt make a difference
		//anything after this comment needs to move to L1 now
		else if (VICTIM[0].tag == tag){ cout << "Read" << VICTIM[0].data << "from VICTIM[0]. Address was" << adr; this->myStat.missL1 += 1;}
		else if (VICTIM[1].tag == tag){ cout << "Read" << VICTIM[1].data << "from VICTIM[1]. Address was" << adr; this->myStat.missL1 += 1;}
		else if (VICTIM[2].tag == tag){ cout << "Read" << VICTIM[2].data << "from VICTIM[2]. Address was" << adr; this->myStat.missL1 += 1;}
		else if (VICTIM[3].tag == tag){ cout << "Read" << VICTIM[3].data << "from VICTIM[3]. Address was" << adr; this->myStat.missL1 += 1;}


		else if (L2[index][0].tag == tag){ cout << "Read" << L2[index][0].data << "from L2[0]. Address was" << adr; this->myStat.missL1 += 1; this->myStat.missVic += 1;}
		else if (L2[index][1].tag == tag){ cout << "Read" << L2[index][1].data << "from L2[1]. Address was" << adr; this->myStat.missL1 += 1; this->myStat.missVic += 1;}
		else if (L2[index][2].tag == tag){ cout << "Read" << L2[index][2].data << "from L2[2]. Address was" << adr; this->myStat.missL1 += 1; this->myStat.missVic += 1;}
		else if (L2[index][3].tag == tag){ cout << "Read" << L2[index][3].data << "from L2[3]. Address was" << adr; this->myStat.missL1 += 1; this->myStat.missVic += 1;}
		else if (L2[index][4].tag == tag){ cout << "Read" << L2[index][4].data << "from L2[4]. Address was" << adr; this->myStat.missL1 += 1; this->myStat.missVic += 1;}
		else if (L2[index][5].tag == tag){ cout << "Read" << L2[index][5].data << "from L2[5]. Address was" << adr; this->myStat.missL1 += 1; this->myStat.missVic += 1;}
		else if (L2[index][6].tag == tag){ cout << "Read" << L2[index][6].data << "from L2[6]. Address was" << adr; this->myStat.missL1 += 1; this->myStat.missVic += 1;}
		else if (L2[index][7].tag == tag){ cout << "Read" << L2[index][7].data << "from L2[7]. Address was" << adr; this->myStat.missL1 += 1; this->myStat.missVic += 1;}
		//so that means the requested info is not available at all, but the index might exist with the tag wrong
		//now we need to locate a cache block to use*/
		int index = adr & 0b111111; //2 bit block offset
		index = index;
		int tag = adr >> 6; //2 bit block offset
		int vtag = adr;
		//cout << "\njust defined index, it is currently: " << index;

		// Check L1 cache
		//cout << "\n(L1[index].tag == tag && L1[index].valid == 1) " << L1[index].tag << " == " << tag << " && " << L1[index].valid;
		if (L1[index].tag == tag && L1[index].valid == 1) {
			//cout << "\nRead " << L1[index].data << " from L1. Address was " << adr;
			this->myStat.accL1 += 1;
			return; // No need to check VICTIM or L2 if found in L1
		}//if it tried to read from an odd address im not sure it would work here
		this->myStat.missL1 += 1;
		// Check VICTIM cache
		for (int i = 0; i < VICTIM_SIZE; ++i) {
			//cout << "\nchecking victim cache";
			//cout << "\ntag im looking for is " << vtag;
			//cout << "\nVICTIM[" << i << "].tag is " << VICTIM[i].tag;
			//cout << "\nVICTIM[" << i << "].valid is " << VICTIM[i].valid;
			//cout << "\nVICTIM[" << i << "].data is " << VICTIM[i].data;
			//cout << "\nVICTIM[" << i << "].lru_position is " << VICTIM[i].lru_position;
			if (VICTIM[i].tag == vtag && VICTIM[i].valid == 1) { //found in victim cache
				//cout << "\nRead " << VICTIM[i].data << " from VICTIM[" << i << "]. Address was " << adr;
				//VICTIM[i].lru_position = 0; // just to be safe
				for (int j = 0; j < VICTIM_SIZE; ++j) { //i increment the rest of the blocks
					if (VICTIM[j].valid) {
						VICTIM[j].lru_position += 1;
					}
				}
				cacheBlock tempA = L1[index - (index % 4) + 0];
				cacheBlock tempB = L1[index - (index % 4) + 1];
				cacheBlock tempC = L1[index - (index % 4) + 2];
				cacheBlock tempD = L1[index - (index % 4) + 3];
				L1[index - (index % 4) + 0] = VICTIM[i - (i % 4) + 0];
				L1[index - (index % 4) + 1] = VICTIM[i - (i % 4) + 1];
				L1[index - (index % 4) + 2] = VICTIM[i - (i % 4) + 2];
				L1[index - (index % 4) + 3] = VICTIM[i - (i % 4) + 3];
				L1[index - (index % 4) + 0].tag = tag;
				L1[index - (index % 4) + 1].tag = tag;
				L1[index - (index % 4) + 2].tag = tag;
				L1[index - (index % 4) + 3].tag = tag;
				VICTIM[i - (i % 4) + 0] = tempA;
				VICTIM[i - (i % 4) + 1] = tempB;
				VICTIM[i - (i % 4) + 2] = tempC;
				VICTIM[i - (i % 4) + 3] = tempD;
				VICTIM[i - (i % 4) + 0].tag = index - (index % 4) + 0 | tempA.tag << 6;
				VICTIM[i - (i % 4) + 1].tag = index - (index % 4) + 0 | tempB.tag << 6;
				VICTIM[i - (i % 4) + 2].tag = index - (index % 4) + 0 | tempC.tag << 6;
				VICTIM[i - (i % 4) + 3].tag = index - (index % 4) + 0 | tempD.tag << 6;
				VICTIM[i - (i % 4) + 0].lru_position = 0;
				VICTIM[i - (i % 4) + 1].lru_position = 0;
				VICTIM[i - (i % 4) + 2].lru_position = 0;
				VICTIM[i - (i % 4) + 3].lru_position = 0;
				//i need to now move this to L1
				//the item evicted in L1 needs to move down here if it has something. there will guranteed be something there already
				this->myStat.accVI += 1;
				return; // No need to check L2 if found in VICTIM
			}
		}
		this->myStat.missVI += 1;

		// Check L2 cache
		for (int i = 0; i < 8; ++i) {
			//cout << "\nchecking l2 cache";
			//cout << "\nindex is " << index;
			//cout << "\ntag im looking for is " << tag;
			//cout << "\nL2[" << index << "][" << i << "].tag is " << L2[index][i].tag;
			//cout << "\nL2[" << index << "][" << i << "].valid is " << L2[index][i].valid;
			//cout << "\nL2[" << index << "][" << i << "].data is " << L2[index][i].data;
			//cout << "\nL2[" << index << "][" << i << "].lru_position is " << L2[index][i].lru_position;
			if (L2[index][i].tag == tag && L2[index][i].valid == 1) { //found it
				//cout << "\nRead " << L2[index][i].data << " from L2[" << i << "]. Address was " << adr;
				this->myStat.accL2 += 1;
				//temp will always have something
				cacheBlock tempA = L1[index - (index % 4) + 0]; 
				cacheBlock tempB = L1[index - (index % 4) + 1]; 
				cacheBlock tempC = L1[index - (index % 4) + 2]; 
				cacheBlock tempD = L1[index - (index % 4) + 3]; 
				L1[index - (index % 4) + 0] = L2[index - (index % 4) + 0][i];
				L1[index - (index % 4) + 1] = L2[index - (index % 4) + 1][i];
				L1[index - (index % 4) + 2] = L2[index - (index % 4) + 2][i];
				L1[index - (index % 4) + 3] = L2[index - (index % 4) + 3][i];
				L2[index - (index % 4) + 0][i].data = 0;
				L2[index - (index % 4) + 1][i].data = 0;
				L2[index - (index % 4) + 2][i].data = 0;
				L2[index - (index % 4) + 3][i].data = 0;
				L2[index - (index % 4) + 0][i].tag = 0;
				L2[index - (index % 4) + 1][i].tag = 0;
				L2[index - (index % 4) + 2][i].tag = 0;
				L2[index - (index % 4) + 3][i].tag = 0;
				L2[index - (index % 4) + 0][i].valid = 0;
				L2[index - (index % 4) + 1][i].valid = 0;
				L2[index - (index % 4) + 2][i].valid = 0;
				L2[index - (index % 4) + 3][i].valid = 0;
				L2[index - (index % 4) + 0][i].lru_position = 0;
				L2[index - (index % 4) + 1][i].lru_position = 0;
				L2[index - (index % 4) + 2][i].lru_position = 0;
				L2[index - (index % 4) + 3][i].lru_position = 0;
				
				int maxIndexL1 = 0; //finding the VICTIM entry with highest lru if VICTIM is full
				for (int i = 0; i < VICTIM_SIZE; ++i) {
					if (VICTIM[i].lru_position > VICTIM[maxIndexL1].lru_position) {
						maxIndexL1 = i;
					}
				}
				//cout << "\nlargest entry was VICTIM[" << maxIndexL1 << "] with a value of " << VICTIM[maxIndexL1].data * 4; 
				for (int i = 0; i < VICTIM_SIZE; ++i){if (VICTIM[i].valid == 1) VICTIM[i].lru_position++;}


				//cout << "\nVICTIM[maxIndexL1].data: " << VICTIM[maxIndexL1].data;
				//cout << "\nVICTIM[maxIndexL1].tag: " << VICTIM[maxIndexL1].tag;
				//cout << "\nVICTIM[maxIndexL1].valid: " << VICTIM[maxIndexL1].valid;
				cacheBlock tempE = VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 0];
				cacheBlock tempF = VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 1];
				cacheBlock tempG = VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 2];
				cacheBlock tempH = VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 3];
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 0] = tempA;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 1] = tempB;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 2] = tempC;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 3] = tempD;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 0].tag = index | tempA.tag << 6;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 1].tag = index | tempB.tag << 6;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 2].tag = index | tempC.tag << 6;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 3].tag = index | tempD.tag << 6;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 0].lru_position = 0;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 1].lru_position = 0;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 2].lru_position = 0;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 3].lru_position = 0;
				int indexA = tempE.tag & 0b111111;
				int indexB = tempD.tag & 0b111111;
				int indexC = tempF.tag & 0b111111;
				int indexD = tempG.tag & 0b111111;

				//index = temp2.tag & 0b1111;
				//cout << "\nnew shifted index is: " << index;
				//cout << "\ntemp2.tag is: " << temp2.tag;
				//cout << "\nnewtag is: " << newtag;
				for (int i = 0; i < L2_CACHE_WAYS; ++i){//if there was an empty spot in the right set
					if (L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][i].valid == 0){
						for (int j = 0; j < L2_CACHE_WAYS; ++j){if (L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][j].valid == 1) L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][j].lru_position++;} // probably an issue
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][i] = tempE;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 1][i] = tempF;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 2][i] = tempG;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 3][i] = tempH;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][i].tag = tempE.tag >> 6;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 1][i].tag = tempF.tag >> 6;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 2][i].tag = tempG.tag >> 6;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 3][i].tag = tempH.tag >> 6;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][i].lru_position = 0;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 1][i].lru_position = 0;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 2][i].lru_position = 0;
						L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 3][i].lru_position = 0;
						/*cout << "\nL1 Cache Data: ";
						for (int i = 0; i < L1_CACHE_SETS; ++i) {
							if (i % 4 == 0) {
								cout << L1[i].data * 4 << " ";
							}
						}

						cout << "\nVI Cache Data: ";
						for (int i = 0; i < VICTIM_SIZE; ++i) {
							if (i % 4 == 0) {
								cout << VICTIM[i].data * 4 << " ";
							}
						}

						cout << "\nL2 Cache Data: ";
						for (int i = 0; i < L2_CACHE_SETS; ++i) {
							if (i % 4 == 0) {
								cout << L2[i][0].data * 4 << " ";
							}
						}

						cout << "\nL1 Cache Valid: ";
						for (int i = 0; i < L1_CACHE_SETS; ++i) {
							if (i % 4 == 0) {
								cout << L1[i].valid << " ";
							}
						}

						cout << "\nVI Cache Valid: ";
						for (int i = 0; i < VICTIM_SIZE; ++i) {
							if (i % 4 == 0) {
								cout << VICTIM[i].valid << " ";
							}
						}

						cout << "\nL2 Cache Valid: ";
						for (int i = 0; i < L2_CACHE_SETS; ++i) {
							if (i % 4 == 0) {
								cout << L2[i][0].valid << " ";
							}
						}

						cout << "\nVI Cache LRU: ";
						for (int i = 0; i < VICTIM_SIZE; ++i) {
							if (i % 4 == 0) {
								cout << VICTIM[i].lru_position << " ";
							}
						}

						cout << "\nL2 Cache LRU: ";
						for (int i = 0; i < L2_CACHE_SETS; ++i) {
							if (i % 4 == 0) {
								cout << L2[i][0].lru_position << " ";
							}
						}*/
						return;
					}	
				}

				int maxIndexL2 = 0; //finding the L2 entry with highest lru if L2 set is full
				for (int i = 0; i < VICTIM_SIZE; ++i) {
					if (L2[index][i].lru_position > L2[index][maxIndexL2].lru_position) {
						maxIndexL2 = i;
					}
				}
				for (int i = 0; i < VICTIM_SIZE; ++i) {if (L2[index][i].valid == 1) L2[index][i].lru_position++;}
				L2[index - (index % 4) + 0][maxIndexL2] = tempE;
				L2[index - (index % 4) + 1][maxIndexL2] = tempF;
				L2[index - (index % 4) + 2][maxIndexL2] = tempG;
				L2[index - (index % 4) + 3][maxIndexL2] = tempH;
				L2[index - (index % 4) + 0][maxIndexL2].tag = tempE.tag >> 6;
				L2[index - (index % 4) + 1][maxIndexL2].tag = tempF.tag >> 6;
				L2[index - (index % 4) + 2][maxIndexL2].tag = tempG.tag >> 6;
				L2[index - (index % 4) + 3][maxIndexL2].tag = tempH.tag >> 6;
				L2[index - (index % 4) + 0][maxIndexL2].lru_position = 0;
				L2[index - (index % 4) + 1][maxIndexL2].lru_position = 0;
				L2[index - (index % 4) + 2][maxIndexL2].lru_position = 0;
				L2[index - (index % 4) + 3][maxIndexL2].lru_position = 0;
				return; //L2 has it and we've finished shuffling
			}
		}
		this->myStat.missL2 += 1;

		//cout << "\nRead " << myMem[adr] << " from memory. Address was " << adr;
/*		cout << "\nL1 Cache Data: ";
		for (int i = 0; i < L1_CACHE_SETS; ++i) {
			if (i % 4 == 0) {
				cout << L1[i].data * 4 << " ";
			}
		}

		cout << "\nVI Cache Data: ";
		for (int i = 0; i < VICTIM_SIZE; ++i) {
			cout << VICTIM[i].data * 4 << " ";
		}

		cout << "\nL2 Cache Data: ";
		for (int i = 0; i < L2_CACHE_WAYS; ++i) {
			cout << L2[0][i].data * 4 << " ";
		}

		cout << "\nL1 Cache Valid: ";
		for (int i = 0; i < L1_CACHE_SETS; ++i) {
			if (i % 4 == 0) {
				cout << L1[i].valid << " ";
			}
		}

		cout << "\nVI Cache Valid: ";
		for (int i = 0; i < VICTIM_SIZE; ++i) {
			cout << VICTIM[i].valid << " ";
		}

		cout << "\nL2 Cache Valid: ";
		for (int i = 0; i < L2_CACHE_WAYS; ++i) {
			cout << L2[0][i].valid << " ";
		}*/



		//cout << "\nBEFORE FUNCTION";

		//int index = adr & 0b111100;
		//index = index >> 2;
		//int tag = adr >> 6;
		//int vtag = adr >> 2;
		if(L1[index].valid == 0){ //if there is an open block 
			L1[index - (index % 4) + 0].data = myMem[adr - (adr % 4) + 0];
			L1[index - (index % 4) + 1].data = myMem[adr - (adr % 4) + 1];
			L1[index - (index % 4) + 2].data = myMem[adr - (adr % 4) + 2];
			L1[index - (index % 4) + 3].data = myMem[adr - (adr % 4) + 3];
			//cout << "\nL1[(index % 4) + 0]: " << (L1[index - (index % 4) + 0].data) * 4;
			//cout << "\nL1[(index % 4) + 1]: " << (L1[index - (index % 4) + 1].data) * 4;
			//cout << "\nL1[(index % 4) + 2]: " << (L1[index - (index % 4) + 2].data) * 4;
			//cout << "\nL1[(index % 4) + 3]: " << (L1[index - (index % 4) + 3].data) * 4;
			//cout << "\nmyMem[(adr % 4) + 0]: " << (L1[index - (index % 4) + 0].data) * 4;
			//cout << "\nmyMem[(adr % 4) + 1]: " << (L1[index - (index % 4) + 1].data) * 4;
			//cout << "\nmyMem[(adr % 4) + 2]: " << (L1[index - (index % 4) + 2].data) * 4;
			//cout << "\nmyMem[(adr % 4) + 3]: " << (L1[index - (index % 4) + 3].data) * 4;
			L1[index - (index % 4) + 0].lru_position = 0;
			L1[index - (index % 4) + 1].lru_position = 0;
			L1[index - (index % 4) + 2].lru_position = 0;
			L1[index - (index % 4) + 3].lru_position = 0;
			L1[index - (index % 4) + 0].tag = tag;
			L1[index - (index % 4) + 1].tag = tag;
			L1[index - (index % 4) + 2].tag = tag;
			L1[index - (index % 4) + 3].tag = tag;
			L1[index - (index % 4) + 0].valid = 1;
			L1[index - (index % 4) + 1].valid = 1;
			L1[index - (index % 4) + 2].valid = 1;
			L1[index - (index % 4) + 3].valid = 1;
			//cout << "\nMoving " << myMem[adr]*4 << " from memory to L1. Address was " << adr/4;
			return;
		}
		else if (L1[index].valid == 1){ //if there is a conflict, which is not guaranteed
			cacheBlock tempA = L1[index - (index % 4) + 0]; //temp will always have something //NOT TRUE
			cacheBlock tempB = L1[index - (index % 4) + 1]; //temp will always have something //NOT TRUE
			cacheBlock tempC = L1[index - (index % 4) + 2]; //temp will always have something //NOT TRUE
			cacheBlock tempD = L1[index - (index % 4) + 3]; //temp will always have something //NOT TRUE
			L1[index - (index % 4) + 0].data = myMem[adr - (adr % 4) + 0];
			L1[index - (index % 4) + 1].data = myMem[adr - (adr % 4) + 1];
			L1[index - (index % 4) + 2].data = myMem[adr - (adr % 4) + 2];
			L1[index - (index % 4) + 3].data = myMem[adr - (adr % 4) + 3];
			L1[index - (index % 4) + 0].lru_position = 0;
			L1[index - (index % 4) + 1].lru_position = 0;
			L1[index - (index % 4) + 2].lru_position = 0;
			L1[index - (index % 4) + 3].lru_position = 0;
			L1[index - (index % 4) + 0].tag = tag;
			L1[index - (index % 4) + 1].tag = tag; //this doesnt seem right
			L1[index - (index % 4) + 2].tag = tag;
			L1[index - (index % 4) + 3].tag = tag;
			L1[index - (index % 4) + 0].valid = 1;
			L1[index - (index % 4) + 1].valid = 1;
			L1[index - (index % 4) + 2].valid = 1;
			L1[index - (index % 4) + 3].valid = 1;

			// Check if there are any open spaces in the VICTIM array
			bool hasOpenSpaceV = false;
			int soonestAvailableIndexV = -1; // Initialize with an invalid index

			for (int i = 0; i < VICTIM_SIZE; ++i) {
				if (VICTIM[i].valid == 0) {
					hasOpenSpaceV = true;
					soonestAvailableIndexV = i; // Update the index of the soonest available unit
					break; // Exit the loop if an open space is found
				}
			}
			if (hasOpenSpaceV){//VICTIM IS NOT FULL
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 0] = tempA;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 1] = tempB;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 2] = tempC;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 3] = tempD;
				//cout << "\ntemp1.tag: " << temp1.tag;
				//cout << "\ntemp1.data: " << temp1.data;
				//cout << "\ntemp1.valid: " << temp1.valid;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 0].tag = index - (index % 4) + 0 | tempA.tag << 6;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 1].tag = index - (index % 4) + 0 | tempB.tag << 6;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 2].tag = index - (index % 4) + 0 | tempC.tag << 6;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 3].tag = index - (index % 4) + 0 | tempD.tag << 6;
				//cout << "\nVICTIM[soonestAvailableIndexV].tag: " << VICTIM[soonestAvailableIndexV].tag;
				//cout << "\nadr: " << adr;
				for(int i = 0; i < VICTIM_SIZE; i++){
					if (VICTIM[i].valid == 1) VICTIM[i].lru_position++;
				}
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 0].lru_position = 0;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 1].lru_position = 0;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 2].lru_position = 0;
				VICTIM[soonestAvailableIndexV - (soonestAvailableIndexV % 4) + 3].lru_position = 0;
				//cout << "\nVictim is not full, but L1 was. Moving " << temp1.data*4 << " from L1 to VICTIM. Address was " << adr/4;
				return;
			}
			else if (!hasOpenSpaceV){//VICTIM IS FULL
				//cout << "\nVICTIM IS FULL";
				int maxIndexL1 = 0; //finding the VICTIM entry with highest lru if VICTIM is full
				for (int i = 0; i < VICTIM_SIZE; ++i) {
					if (VICTIM[i].lru_position > VICTIM[maxIndexL1].lru_position) {
						maxIndexL1 = i;
					}
				}
				for(int i = 0; i<VICTIM_SIZE; ++i){if (VICTIM[i].valid == 1) VICTIM[i].lru_position++;}
				cacheBlock tempE = VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 0];
				cacheBlock tempF = VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 1];
				cacheBlock tempG = VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 2];
				cacheBlock tempH = VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 3];
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 0] = tempA;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 1] = tempB;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 2] = tempC;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 3] = tempD;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 0].tag = index | tempA.tag << 6;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 1].tag = index | tempB.tag << 6;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 2].tag = index | tempC.tag << 6;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 3].tag = index | tempD.tag << 6;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 0].lru_position = 0;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 1].lru_position = 0;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 2].lru_position = 0;
				VICTIM[maxIndexL1 - (maxIndexL1 % 4) + 3].lru_position = 0;

				int indexA = tempE.tag & 0b111111;
				int indexB = tempF.tag & 0b111111;
				int indexC = tempG.tag & 0b111111;
				int indexD = tempH.tag & 0b111111;
				//cout << "\nnew shifted index is: " << index;
				bool hasOpenSpaceL2 = false;
				int soonestAvailableIndexL2 = -1; // Initialize with an invalid index
				for (int i = 0; i < L2_CACHE_WAYS; ++i){//if there was an empty spot in the right set
					if (L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][i].valid == 0){
						hasOpenSpaceL2 = true;
						soonestAvailableIndexL2 = i;
						break;
					}	
				}
				if (hasOpenSpaceL2){
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][soonestAvailableIndexL2] = tempE;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 1][soonestAvailableIndexL2] = tempF;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 2][soonestAvailableIndexL2] = tempG;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 3][soonestAvailableIndexL2] = tempH;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][soonestAvailableIndexL2].tag = tempE.tag >> 6;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 1][soonestAvailableIndexL2].tag = tempF.tag >> 6;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 2][soonestAvailableIndexL2].tag = tempG.tag >> 6;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 3][soonestAvailableIndexL2].tag = tempH.tag >> 6;
					//cout << "\nindex: " << index;
					//cout << "\nsoonestAvailableIndexL2: " << soonestAvailableIndexL2;
					//cout << "\ntemp2.data: " << tempE.data;
					//cout << "\ntemp2.tag: " << tempE.tag;
					//cout << "\nnewtag: " << tempE.tag >> 4;
					//cout << "\ntempE.valid: " << tempE.valid;
					//cout << "\ntempF.valid: " << tempF.valid;
					//cout << "\ntempG.valid: " << tempG.valid;
					//cout << "\ntempH.valid: " << tempH.valid;
					//cout << "\n(L2[(tempE.tag & 0b1111) - ((tempE.tag & 0b1111) % 4) + 0][soonestAvailableIndexL2].valid: " << L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][soonestAvailableIndexL2].valid;
					//cout << "\n(L2[(tempE.tag & 0b1111) - ((tempE.tag & 0b1111) % 4) + 1][soonestAvailableIndexL2].valid: " << L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 1][soonestAvailableIndexL2].valid;
					//cout << "\n(L2[(tempE.tag & 0b1111) - ((tempE.tag & 0b1111) % 4) + 2][soonestAvailableIndexL2].valid: " << L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 2][soonestAvailableIndexL2].valid;
					//cout << "\n(L2[(tempE.tag & 0b1111) - ((tempE.tag & 0b1111) % 4) + 3][soonestAvailableIndexL2].valid: " << L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 3][soonestAvailableIndexL2].valid;
					//cout << "\nsetting L2[" << index << "][" << soonestAvailableIndexL2 << "] to temp2";
					//cout << "\nvalid bit for this new entry is: " << L2[index][soonestAvailableIndexL2].valid;
					for (int i = 0; i < L2_CACHE_WAYS; ++i) { //i increment the rest of the blocks
						if (L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][i].valid) {
							L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][i].lru_position += 1;
						}
					}
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 0][soonestAvailableIndexL2].lru_position = 0;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 1][soonestAvailableIndexL2].lru_position = 0;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 2][soonestAvailableIndexL2].lru_position = 0;
					L2[(tempE.tag & 0b111111) - ((tempE.tag & 0b111111) % 4) + 3][soonestAvailableIndexL2].lru_position = 0;
					//cout << "\nsoonestAvailableIndexL2: " << soonestAvailableIndexL2;
					//cout << "\nL2 is not full, but VICTIM was. Moving " << tempE.data*4 << " from VICTIM to L2. Address was " << adr/4;
					return;
				}
				else if(!hasOpenSpaceL2){
					int maxIndexL2 = 0; //finding the L2 entry with highest lru if L2 set is full
					for (int i = 0; i < L2_CACHE_WAYS; ++i) {
						if (L2[index][i].lru_position > L2[index][maxIndexL2].lru_position) {
							maxIndexL2 = i;
						}
					}
					for(int i = 0; i<L2_CACHE_WAYS; ++i){if (L2[index][i].valid == 1) L2[index][i].lru_position++;}
					L2[index - (index % 4) + 0][maxIndexL2] = tempE;
					L2[index - (index % 4) + 1][maxIndexL2] = tempF;
					L2[index - (index % 4) + 2][maxIndexL2] = tempG;
					L2[index - (index % 4) + 3][maxIndexL2] = tempH;
					L2[index - (index % 4) + 0][maxIndexL2].lru_position = 0;
					L2[index - (index % 4) + 1][maxIndexL2].lru_position = 0;
					L2[index - (index % 4) + 2][maxIndexL2].lru_position = 0;
					L2[index - (index % 4) + 3][maxIndexL2].lru_position = 0;
					//cout << "\nL2 is full, but L1 was. Moving " << tempE.data*4 << " from VICTIM to TRASH. Address was " << adr/4;
					return;
				}
			}
		}
	}
	else if (MemW){ //handle store
	//handle eviction for L1 into victim, and victim into L2, and L2 into memory //actually no L2 into memory, memory should always be updated
		//cout << "\nrunning a store";
		int index = adr & 0b111111; //2 bit block offset
		index = index;
		int tag = adr >> 6; //2 bit block offset
		int vtag = adr;
		//cout << "\nindex is: " << index;
		//cout << "\ndata is: " << *data;
		//cout << "\nL1[index].tag == (tag - (tag % 16)) && L1[index].valid == 1){ L1[index].data = *data;";
		//cout << "\n" << L1[index].tag << " == " << tag << " && " << VICTIM[0].valid;
		//cout << "\n" << (L1[index].tag == tag) && (L1[index].valid == 1);
		if ((L1[index].tag == tag) && (L1[index].valid == 1)){ L1[index].data = *data; ;}//if exists inside the block, overwrite it
		else if ((VICTIM[0].tag == (vtag - (vtag % 16))) && (VICTIM[0].valid == 1)){ VICTIM[0].data = *data; }
		else if ((VICTIM[1].tag == (vtag - (vtag % 16))) && (VICTIM[1].valid == 1)){ VICTIM[1].data = *data; }
		else if ((VICTIM[2].tag == (vtag - (vtag % 16))) && (VICTIM[2].valid == 1)){ VICTIM[2].data = *data; }
		else if ((VICTIM[3].tag == (vtag - (vtag % 16))) && (VICTIM[3].valid == 1)){ VICTIM[3].data = *data; }
		else if ((VICTIM[4].tag == (vtag - (vtag % 16))) && (VICTIM[4].valid == 1)){ VICTIM[4].data = *data; }
		else if ((VICTIM[5].tag == (vtag - (vtag % 16))) && (VICTIM[5].valid == 1)){ VICTIM[5].data = *data; }
		else if ((VICTIM[6].tag == (vtag - (vtag % 16))) && (VICTIM[6].valid == 1)){ VICTIM[6].data = *data; }
		else if ((VICTIM[7].tag == (vtag - (vtag % 16))) && (VICTIM[7].valid == 1)){ VICTIM[7].data = *data; }
		else if ((VICTIM[8].tag == (vtag - (vtag % 16))) && (VICTIM[8].valid == 1)){ VICTIM[8].data = *data; }
		else if ((VICTIM[9].tag == (vtag - (vtag % 16))) && (VICTIM[9].valid == 1)){ VICTIM[9].data = *data; }
		else if ((VICTIM[10].tag == (vtag - (vtag % 16))) && (VICTIM[10].valid == 1)){ VICTIM[10].data = *data; }
		else if ((VICTIM[11].tag == (vtag - (vtag % 16))) && (VICTIM[11].valid == 1)){ VICTIM[11].data = *data; }
		else if ((VICTIM[12].tag == (vtag - (vtag % 16))) && (VICTIM[12].valid == 1)){ VICTIM[12].data = *data; }
		else if ((VICTIM[13].tag == (vtag - (vtag % 16))) && (VICTIM[13].valid == 1)){ VICTIM[13].data = *data; }
		else if ((VICTIM[14].tag == (vtag - (vtag % 16))) && (VICTIM[14].valid == 1)){ VICTIM[14].data = *data; }
		else if ((VICTIM[15].tag == (vtag - (vtag % 16))) && (VICTIM[15].valid == 1)){ VICTIM[15].data = *data; }
		else if ((L2[index][0].tag == (tag - (tag % 16))) && (L2[index][0].valid == 1)){ L2[index][0].data = *data; }
		else if ((L2[index][1].tag == (tag - (tag % 16))) && (L2[index][1].valid == 1)){ L2[index][1].data = *data; }
		else if ((L2[index][2].tag == (tag - (tag % 16))) && (L2[index][2].valid == 1)){ L2[index][2].data = *data; }
		else if ((L2[index][3].tag == (tag - (tag % 16))) && (L2[index][3].valid == 1)){ L2[index][3].data = *data; }
		else if ((L2[index][4].tag == (tag - (tag % 16))) && (L2[index][4].valid == 1)){ L2[index][4].data = *data; }
		else if ((L2[index][5].tag == (tag - (tag % 16))) && (L2[index][5].valid == 1)){ L2[index][5].data = *data; }
		else if ((L2[index][6].tag == (tag - (tag % 16))) && (L2[index][6].valid == 1)){ L2[index][6].data = *data; }
		else if ((L2[index][7].tag == (tag - (tag % 16))) && (L2[index][7].valid == 1)){ L2[index][7].data = *data; }
		myMem[adr] = *data;
		return;
	}
}