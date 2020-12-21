#include <iostream>
#include <string>
using namespace std;

#define PRIME 2147483647;


class DoubleHash {
	int* hashTable;
	int curr_size;
	int tableSize;
	int hash1_a;
	int hash1_b;
	int hash2_a;
	int hash2_b;

public:
	int get_size() {
		return curr_size;
	}

	bool isFull() {
		return (curr_size == tableSize);
	}

	int hash1Int(int key) {
		return (hash1_a*key + hash1_b) % tableSize;
	}

	int hash2Int(int key) {
		int index = (hash1_a*key + hash2_b) % tableSize;
		if (index % 2 == 0 ) {
			return index + 1;
		}
		else {
            return index;
		}
	}

	int doubleHashFuntion(int hash1, int hash2, int i) {
		return (hash1 + i * hash2) % tableSize;
	}


	DoubleHash(int size, int a1, int b1, int a2, int b2) {
		cout << " Start Double" << endl;

		this->tableSize = size;
		this->hash1_a = a1;
		this->hash1_b = b1;
		this->hash2_a = a2;
		this->hash2_b = b2;
		hashTable = new int[tableSize];
		curr_size = 0;
		for (int i = 0; i < tableSize; i++) {
			hashTable[i] = -1;
		}
	}

	void insertHash(int key) {
		if (isFull()) {
			return;
		}

		int index1 = hash1Int(key);
		if (hashTable[index1] != -1) {       // collision occurs 
			int index2 = hash2Int(key);        // get index2 from second hash 
			int i = 1;
			while (1) {
				int newIndex = doubleHashFuntion(index1, index2, i);   //newIndex 
				//cout << index1<<" "<< index2<<"  "<<newIndex<< endl;
				if (hashTable[newIndex] == -1 || hashTable[newIndex] == 0) {  // if then no collision occurs, write in table
					hashTable[newIndex] = key;
					break;
				}
				i++;
			}
		}
		else {        // no collision occurs 
			hashTable[index1] = key;
		}

		curr_size++;
	}

	void search(int key) {
		int index1 = hash1Int(key);
		int index2 = hash2Int(key);
		int i = 0;
		while (hashTable[doubleHashFuntion(index1, index2, i)] != key) {
			if (hashTable[doubleHashFuntion(index1, index2, i)] == -1) {
				cout << key << " does not exist" << endl;
				return;
			}
			i++;
		}
		//cout << key << " found!  index " << (index1 + i * index2) % tableSize << endl;
	}


	void printHash() {
		for (int i = 0; i < tableSize; i++) {
			if (hashTable[i] != -1 && hashTable[i] != 0) {
				cout << i << " --> " << hashTable[i] << endl;
			}
			else {
				cout << i << endl;
			}
		}
	}

	void deleteHash(int key) {
		int index1 = hash1Int(key);
		int index2 = hash2Int(key);
		int i = 0;
		while (hashTable[doubleHashFuntion(index1, index2, i)] != key) {
			if (hashTable[doubleHashFuntion(index1, index2, i)] == -1) {
				cout << key << " does not exist" << endl;
				return;
			}
			i++;
		}
		hashTable[(index1 + i * index2) % tableSize] = 0;
	}
};



class DoubleHashStr {
	string* hashTable;
	int curr_size;
	int tableSize;
	int hash1_a;
	int hash2_a;

public:
	int get_size() {
		return curr_size;
	}

	bool isFull() {
		return (curr_size == tableSize);
	}

	int hash1Int(string key) {
		int h = 5381;
		for (int i = 0; i < key.size(); ++i) {
			h = ((h*hash1_a) + key[i]) % PRIME;
		}
		h = h % tableSize;
		return h;

	}

	int hash2Int(string key) {
		int h = 5381;
		for (int i = 0; i < key.size(); ++i) {
			h = ((h*hash2_a) + key[i]) % PRIME;
		}
		h = h % tableSize;
		if (h % 2 == 0) {
			return h + 1;
		}
		else {
			return h;
		}

	}

	int doubleHashFuntion(int hash1, int hash2, int i) {
		return (hash1 + i * hash2) % tableSize;
	}


	DoubleHashStr(int size, int a1, int a2) {
		cout << "D "<<endl;
		this->tableSize = size;
		this->hash1_a = a1;
		this->hash2_a = a2;
		hashTable = new string[tableSize];
		curr_size = 0;
		for (int i = 0; i < tableSize; i++) {
			hashTable[i] = "-1";
		}
		
	}

	void insertHash(string key) {
		if (isFull()) {
			return;
		}

		int index1 = hash1Int(key);
		if (hashTable[index1] != "-1") {       // collision occurs 
			int index2 = hash2Int(key);        // get index2 from second hash 
			int i = 1;
			while (1) {
				int newIndex = doubleHashFuntion(index1, index2, i);   //newIndex 
				//cout << index1<<" "<< index2<<"  "<<newIndex<< endl;
				if (hashTable[newIndex] == "-1" || hashTable[newIndex] == "0") {  // if then no collision occurs, write in table
					hashTable[newIndex] = key;
					break;
				}
				i++;
			}
		}
		else {        // no collision occurs 
			hashTable[index1] = key;
		}

		curr_size++;
	}

	void search(string key) {
		int index1 = hash1Int(key);
		int index2 = hash2Int(key);
		int i = 0;
		while (hashTable[doubleHashFuntion(index1, index2, i)] != key) {
			if (hashTable[doubleHashFuntion(index1, index2, i)] == "-1") {
				cout << key << " does not exist" << endl;
				return;
			}
			i++;
		}
		//cout << key << " found!  index " << doubleHashFunction(index1,index2,i) << endl;
	}

	void printHash() {
		for (int i = 0; i < tableSize; i++) {
			if (hashTable[i] != "-1" && hashTable[i] != "0") {
				cout << i << " --> " << hashTable[i] << endl;
			}
			else {
				cout << i << endl;
			}
		}
	}

	void deleteHash(string key) {
		int index1 = hash1Int(key);
		int index2 = hash2Int(key);
		int i = 0;
		while (hashTable[doubleHashFuntion(index1, index2, i)] != key) {
			if (hashTable[doubleHashFuntion(index1, index2, i)] == "-1") {
				cout << key << " does not exist" << endl;
				return;
			}
			i++;
		}
		hashTable[doubleHashFuntion(index1,index2,i)] = "0";
	}
};
