#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <random>
#include <ctime>
#include <iomanip>
#include <ctime>
#include <vector>
#include <stdio.h> 
#include <time.h>
using namespace std;
int p = 2147483647;
std::mt19937 gen(time(0)); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> distribution_a(1, p);
std::uniform_int_distribution<> distribution_b(0, p - 1);


class Hash_string
{
	int BUCKET;
	int a = distribution_a(gen);
	list<string> *table;

public:

	Hash_string(int V);  // Constructor 

	// inserts a key into hash table 
	void insertItem(string x);

	// deletes a key from hash table 
	void deleteItem(string key);

	int searchItem(string key);

	// hash function to map values to key 
	int hashFunction(string x) {
		unsigned long long h = 5381;
		for (int i = 0; i < x.size(); ++i) {
			h = ((h*a) + x[i]) % p;
		}
		h = h % BUCKET;
		return h;
	}

	void displayHash();
};

Hash_string::Hash_string(int len_table)
{
	this->BUCKET = len_table;
	table = new list<string>[BUCKET];

}

void Hash_string::insertItem(string key)
{

	int index = hashFunction(key);

	table[index].push_back(key);
}

int Hash_string::searchItem(string key) {

	int index = hashFunction(key);
	// find the key in (inex)th list 
	list <string> ::iterator i;
	int place_in_list = 0;
	for (i = table[index].begin();
		i != table[index].end(); i++) {
		if (*i == key)
			break;
		place_in_list++;
	}
	return place_in_list;
}
void Hash_string::deleteItem(string key)
{
	// get the hash index of key 
	int index = hashFunction(key);

	// find the key in (inex)th list 
	list <string> ::iterator i;
	for (i = table[index].begin();
		i != table[index].end(); i++) {
		if (*i == key)
			break;
	}

	// if key is found in hash table, remove it 
	if (i != table[index].end())
		table[index].erase(i);
}

// function to display hash table 
void Hash_string::displayHash() {
	for (int i = 0; i < BUCKET; i++) {
		cout << i;
		for (auto x : table[i])
			cout << " --> " << x;
		cout << endl;
	}
}


//-------HASH TABLE FOR INTEGER----------
class Hash_int
{
	int BUCKET;
	int a = distribution_a(gen);
	int b = distribution_b(gen);
	list<int> *table;

public:

	Hash_int(int V);  // Constructor 

	// inserts a key into hash table 
	void insertItem(int x);

	// deletes a key from hash table 
	void deleteItem(int key);

	int searchItem(int key);

	// hash function to map values to key 
	int hashFunction(int x) {
		unsigned long long f = (a*x + b) % p;
		//cout<<"key="<<x<<" a="<<a<<" b="<<b<<endl;
		//cout<<f<<"    "<<f % BUCKET<<endl;
		return (f % BUCKET);
	}

	void displayHash();
};

Hash_int::Hash_int(int len_table)
{
	this->BUCKET = len_table;
	table = new list<int>[BUCKET];

}

void Hash_int::insertItem(int key)
{

	int index = hashFunction(key);

	table[index].push_back(key);
}

int Hash_int::searchItem(int key) {

	int index = hashFunction(key);
	// find the key in (inex)th list 
	list <int> ::iterator i;
	int place_in_list = 0;
	for (i = table[index].begin();
		i != table[index].end(); i++) {
		if (*i == key)
			break;
		place_in_list++;
	}
	return place_in_list;
}
void Hash_int::deleteItem(int key)
{
	// get the hash index of key 
	int index = hashFunction(key);

	// find the key in (inex)th list 
	list <int> ::iterator i;
	for (i = table[index].begin();
		i != table[index].end(); i++) {
		if (*i == key)
			break;
	}

	// if key is found in hash table, remove it 
	if (i != table[index].end())
		table[index].erase(i);
}

// function to display hash table 
void Hash_int::displayHash() {
	for (int i = 0; i < BUCKET; i++) {
		cout << i;
		for (auto x : table[i])
			cout << " --> " << x;
		cout << endl;
	}
}
