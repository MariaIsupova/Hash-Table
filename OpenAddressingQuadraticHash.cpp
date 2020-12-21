#include <iostream>
#include <string>
using namespace std;

#define PRIME 19
#define C1 13
#define C2 7

class OpenAddressingQuadraticHash {
	int* hashTable;
	int curr_size;
	int tableSize;
	int a;
	int b;

public:
	int get_size() {
		return curr_size;
	}

	bool isFull() {
		return (curr_size == tableSize);
	}

	int hash1Int(int key) {

		return (a*key + b) % tableSize;
	}

	int QudraticProb(int hash1, int i) {
		return (hash1 + C1 * i + C2 * i*i) % tableSize;
	}


	OpenAddressingQuadraticHash(int size, int a, int b) {
		//cout << " Start Quadratic" << endl;
		this->tableSize = size;
		this->a = a;
		this->b = b;
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
			int i = 1;
			while (1) {
				int newIndex = QudraticProb(index1, i);   //newIndex 
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
		int i = 0;
		while (hashTable[QudraticProb(index1, i)] != key) {
			if (hashTable[QudraticProb(index1, i)] == -1) {
				//cout << key << " does not exist" << endl;
				return;
			}
			i++;
		}
		//cout << key << " found!  index " << QudraticProb(index1, i);
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
		int i = 0;
		while (hashTable[QudraticProb(index1, i)] != key) {
			if (hashTable[QudraticProb(index1, i)] == -1) {
				cout << key << " does not exist" << endl;
				return;
			}
			i++;
		}
		hashTable[QudraticProb(index1, i)] = 0;
		curr_size--;
		//cout << key << " delete in " << QudraticProb(index1, i) << " position  ";
	}
};



class OpenAddressingQuadraticHashStr {
	string* hashTable;
	int curr_size;
	int tableSize;
	int a;
	int b;

public:
	int get_size() {
		return curr_size;
	}

	bool isFull() {
		return (curr_size == tableSize);
	}

	int hash1String(string key) {
		int h = 5381;
		for (int i = 0; i < key.size(); ++i) {
			h = ((h*a) + key[i]) % PRIME;
		}
		h = h % tableSize;
		return h;
	}

	int QudraticProb(int hash1, int i) {
		return (hash1 + C1 * i + C2 * i*i) % tableSize;
	}


	OpenAddressingQuadraticHashStr(int size, int a, int b) {
		cout << "Q ";
		this->tableSize = size;
		this->a = a;
		this->b = b;
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

		int index1 = hash1String(key);
		if (hashTable[index1] != "-1") {       // collision occurs 
			int i = 1;
			while (1) {
				int newIndex = QudraticProb(index1, i);   //newIndex 
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
		int index1 = hash1String(key);
		int i = 0;
		while (hashTable[QudraticProb(index1, i)] != key) {
			if (hashTable[QudraticProb(index1, i)] == "-1") {
				//cout << key << " does not exist" << endl;
				return;
			}
			i++;
		}
		//cout << key << " found!  index " << QudraticProb(index1, i);
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
		int index1 = hash1String(key);
		int i = 0;
		while (hashTable[QudraticProb(index1, i)] != key) {
			if (hashTable[QudraticProb(index1, i)] == "-1") {
				cout << key << " does not exist" << endl;
				return;
			}
			i++;
		}
		hashTable[QudraticProb(index1, i)] = "0";
		curr_size--;
		//cout << key << " delete in " << QudraticProb(index1, i) << " position  ";
	}
};