
#include<iostream>
#include<string>
#include<vector>
#include<math.h>
#include<stdexcept>
#include <cmath>
#include <random>
#include <iomanip>
#include <ctime>
#include <stdio.h> 
#include <time.h>
#include <chrono>
#include <list>
#include<algorithm>
using namespace std;

int p = 2147483647;
char chars[26];
std::mt19937 gen(time(0));
std::uniform_int_distribution<> distribution_a(1, p - 1);
std::uniform_int_distribution<> distribution_b(0, p - 1);

class cuckoo
{
	vector<int> table1;
	vector<int> table2;
	vector<int> coef_hash1;
	vector<int> coef_hash2;
	int len_table;
	int filled_bins = 0;
	int total_capacity;
	int maxTries;
	int hashIndex1(int key);
	int hashIndex2(int key);
	void insertHelper(int key, vector<int> &Table1, vector<int> &Table2, bool whoCalled);
	void rehash();
public:
	cuckoo(int len_table, int capacity);
	int getSize();
	int capacity();
	void insert(int key);
	bool search(int key);
	void Delete(int key);
	void print();

};

cuckoo::cuckoo(int len_table, int capacity)
{
	total_capacity = capacity;
	this->len_table = len_table;
	maxTries = 6 * log(len_table) / log(2);
	//cout<<maxTries;
	for (int i = 0; i < len_table; i++) {
		table1.push_back(-1);
		table2.push_back(-1);
	}
	coef_hash1.push_back(distribution_a(gen));
	coef_hash2.push_back(distribution_a(gen));
	for (int i = 0; i < capacity; i++) {
		coef_hash1.push_back(distribution_b(gen));
		coef_hash2.push_back(distribution_b(gen));
	}
}
int cuckoo::hashIndex1(int key)
{
	unsigned long long index;
	for (int i = 0; i < total_capacity; i++) {
		index += coef_hash1[i] * pow(key, i);
	}
	index = (index % p) % len_table;
	return index;
}

int cuckoo::hashIndex2(int key)
{
	unsigned long long index;
	for (int i = 0; i < total_capacity; i++) {
		index += coef_hash2[i] * pow(key, i);
	}
	index = (index % p) % len_table;
	return index;
}

void cuckoo::insertHelper(int key, vector<int> &Table1, vector<int> &Table2, bool whoCalled)
{

	int index1 = hashIndex1(key);
	int index2 = hashIndex2(key);

	if (Table1[index1] == key || Table2[index2] == key)
		return;

	if (Table1[index1] == -1)
	{
		Table1.at(index1) = key;
		if (whoCalled == 0)
		{
			filled_bins++;
		}
		return;
	}

	else if (Table2[index2] == -1)
	{
		Table2.at(index2) = key;
		if (whoCalled == 0)
		{
			filled_bins++;
		}
		return;
	}
	else
		for (int i = 0; i < maxTries; i++)
		{

			//cout<<"new = "<<key<<"  old1 = "<<Table1[index1]<<"  old2 = "<<Table2[index2]<<endl;
			swap(key, Table1[index1]);
			if (key == -1)
			{
				if (whoCalled == 0)
				{
					filled_bins++;
				}
				return;
			}

			swap(key, Table2[index2]);

			if (key == -1)
			{
				if (whoCalled == 0)
				{
					filled_bins++;
				}
				return;
			}
		}
	rehash();
	insertHelper(key, Table1, Table2, 0);
}

void cuckoo::rehash()
{
	vector<int> new_table1;
	vector<int> new_table2;
	int old_capacity = total_capacity;
	int new_capacity = total_capacity;
	//cout<<"Before rehashing"<<endl;
	//print();
	total_capacity = new_capacity;
	coef_hash1.clear();
	coef_hash2.clear();
	coef_hash1.push_back(distribution_a(gen));
	coef_hash2.push_back(distribution_a(gen));
	for (int i = 0; i < total_capacity; i++) {
		coef_hash1.push_back(distribution_b(gen));
		coef_hash2.push_back(distribution_b(gen));
	}

	for (int i = 0; i < (len_table + pow(len_table, 1 / 2)); i++) {
		new_table1.push_back(-1);
		new_table2.push_back(-1);
	}
	//cout<<"Length table "<<len_table<<endl;
	for (int i = 0; i < len_table; i++)
	{

		if (table1[i] != -1) {
			insertHelper(table1[i], new_table1, new_table2, 1);
			cout << i << " Insert " << table1[i] << endl;
		}
		if (table2[i] != -1) {
			insertHelper(table2[i], new_table1, new_table2, 1);
			cout << i << " Insert " << table2[i] << endl;
		}
	}
	this->len_table = len_table + pow(len_table, 1 / 2);
	this->table1 = new_table1;
	this->table2 = new_table2;
	cout << "After rehashing" << endl;
	//print();
}

void cuckoo::insert(int key)
{

	if (search(key))
	{
		return;
	}

	insertHelper(key, table1, table2, 0);
}

bool cuckoo::search(int key)
{
	int index1 = hashIndex1(key);
	int index2 = hashIndex2(key);
	//cout<<table1[index1]<<' '<<table2[index2]<<endl;

	if (table1[index1] == key || table2[index2] == key)
		return true;
	return false;
}

void cuckoo::Delete(int key)
{
	if (!search(key))
	{
		cout << key << " not found.\n";
		return;
	}

	int index1 = hashIndex1(key);
	int index2 = hashIndex2(key);

	if (table1[index1] == key)
		table1[index1] = -1;
	else if (table2[index2] == key)
		table2[index2] = -1;

	--filled_bins;

	if ((float)(filled_bins) / (float)(total_capacity) < 0.25)
		rehash();
}

void cuckoo::print()
{
	for (int i = 0; i < len_table; i++) {
		cout << "Key table1: " << table1[i] << " at index " << i << "    ";
		cout << "Key table2: " << table2[i] << " at index " << i << endl;
	}
	cout << endl;
}





class cuckooStr
{
	vector<string> table1;
	vector<string> table2;
	vector<int> coef_hash1;
	vector<int> coef_hash2;
	int len_table;
	int filled_bins = 0;
	int total_capacity;
	int maxTries;
	int hashIndex1(string key);
	int hashIndex2(string key);
	void insertHelper(string key, vector<string> &Table1, vector<string> &Table2, bool whoCalled);
	void rehash();
public:
	cuckooStr(int len_table, int capacity);
	int getSize();
	int capacity();
	void insert(string key);
	bool search(string key);
	void Delete(string key);
	void print();

};

cuckooStr::cuckooStr(int len_table, int capacity)
{
	total_capacity = capacity;
	this->len_table = len_table;
	maxTries = 6 * log(len_table) / log(2);
	for (int i = 0; i < len_table; i++) {
		table1.push_back("None");
		table2.push_back("None");
	}
	coef_hash1.push_back(distribution_a(gen));
	coef_hash2.push_back(distribution_a(gen));
	for (int i = 0; i < capacity; i++) {
		coef_hash1.push_back(distribution_b(gen));
		coef_hash2.push_back(distribution_b(gen));
	}
}
int cuckooStr::hashIndex1(string key)
{
	unsigned long long h = 5381;
	for (int i = 0; i < total_capacity; ++i) {
		h = ((h*coef_hash1[i]) + key[i]) % p;
	}
	h = h % len_table;
	return h;
}

int cuckooStr::hashIndex2(string key)
{
	unsigned long long h = 5381;
	for (int i = 0; i < total_capacity; ++i) {
		h = ((h*coef_hash2[i]) + key[i]) % p;
	}
	h = h % len_table;
	return h;
}

void cuckooStr::insertHelper(string key, vector<string> &Table1, vector<string> &Table2, bool whoCalled)
{

	int index1 = hashIndex1(key);
	int index2 = hashIndex2(key);

	if (Table1[index1] == key || Table2[index2] == key)
		return;

	if (Table1[index1] == "None")
	{
		Table1.at(index1) = key;
		if (whoCalled == 0)
		{
			filled_bins++;
		}
		return;
	}

	else if (Table2[index2] == "None")
	{
		Table2.at(index2) = key;
		if (whoCalled == 0)
		{
			filled_bins++;
		}
		return;
	}
	else
		for (int i = 0; i < maxTries; i++)
		{

			swap(key, Table1[index1]);
			if (key == "None")
			{
				if (whoCalled == 0)
				{
					filled_bins++;
				}
				return;
			}

			swap(key, Table2[index2]);

			if (key == "None")
			{
				if (whoCalled == 0)
				{
					filled_bins++;
				}
				return;
			}
		}
	rehash();
	insertHelper(key, Table1, Table2, 0);
}

void cuckooStr::rehash()
{
	vector<string> new_table1;
	vector<string> new_table2;
	int old_capacity = total_capacity;
	int new_capacity = total_capacity;

	total_capacity = new_capacity;
	coef_hash1.clear();
	coef_hash2.clear();
	coef_hash1.push_back(distribution_a(gen));
	coef_hash2.push_back(distribution_a(gen));
	for (int i = 0; i < total_capacity; i++) {
		coef_hash1.push_back(distribution_b(gen));
		coef_hash2.push_back(distribution_b(gen));
	}

	for (int i = 0; i < (len_table + pow(len_table, 1 / 2)); i++) {
		new_table1.push_back("None");
		new_table2.push_back("None");
	}

	for (int i = 0; i < len_table; i++)
	{

		if (table1[i] != "None") {
			insertHelper(table1[i], new_table1, new_table2, 1);
		}
		if (table2[i] != "None") {
			insertHelper(table2[i], new_table1, new_table2, 1);
		}
	}
	this->len_table = len_table + pow(len_table, 1 / 2);
	this->table1 = new_table1;
	this->table2 = new_table2;
}

void cuckooStr::insert(string key)
{

	if (search(key))
	{
		return;
	}

	insertHelper(key, table1, table2, 0);
}

bool cuckooStr::search(string key)
{
	int index1 = hashIndex1(key);
	int index2 = hashIndex2(key);

	if (table1[index1] == key || table2[index2] == key)
		return true;
	return false;
}

void cuckooStr::Delete(string key)
{
	if (!search(key))
	{
		cout << key << " not found.\n";
		return;
	}

	int index1 = hashIndex1(key);
	int index2 = hashIndex2(key);

	if (table1[index1] == key)
		table1[index1] = "None";
	else if (table2[index2] == key)
		table2[index2] = "None";

	--filled_bins;

	if ((float)(filled_bins) / (float)(total_capacity) < 0.25)
		rehash();
}

void cuckooStr::print()
{
	for (int i = 0; i < len_table; i++) {
		cout << "Key table1: " << table1[i] << " at index " << i << "    ";
		cout << "Key table2: " << table2[i] << " at index " << i << endl;
	}
	cout << endl;
}
string gen_string(int len_string) {
	string str;
	for (int l = 0; l <= len_string; l++) {
		str += chars[0 + rand() % 25];
	}
	return str;
}

int main() {
	srand(time(0));
	const int max_len = 10000;
	const int step = 100;
	for (int i = 97, n = 0; i <= 122; ++i, ++n)
	{
		chars[n] = (char)i;
	}

	std::vector< int > CuckooMethodInsertStr;
	std::vector< int > CuckooMethodSearchStr;
	std::vector< int > CuckooMethodDeleteStr;

	for (int k = 100; k < max_len; k = k + step) {
		cuckooStr hash_table_Cuckoo_Str(k, 3);
		for (int i = 0; i < k; i++) {
			int len_string = 1 + rand() % 10;
			string val = gen_string(len_string);
			hash_table_Cuckoo_Str.insert(val);
		}
		int len_string = 1 + rand() % 10;
		string value = gen_string(len_string);

		// ------INSERT------- 
		auto beginInsert = std::chrono::steady_clock::now();
		hash_table_Cuckoo_Str.insert(value);
		auto endInsert = std::chrono::steady_clock::now();
		auto elapsed_msInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - beginInsert);


		// ------SEARCH-------
		auto beginSearch = std::chrono::steady_clock::now();
		hash_table_Cuckoo_Str.search(value);
		auto endSearch = std::chrono::steady_clock::now();
		auto elapsed_msSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - beginSearch);


		// -----DELETE--------
		auto beginDel = std::chrono::steady_clock::now();
		hash_table_Cuckoo_Str.Delete(value);
		auto endDel = std::chrono::steady_clock::now();
		auto elapsed_msDel = std::chrono::duration_cast<std::chrono::nanoseconds>(endDel - beginDel);



		CuckooMethodInsertStr.push_back(elapsed_msInsert.count());
		CuckooMethodSearchStr.push_back(elapsed_msSearch.count());
		CuckooMethodDeleteStr.push_back(elapsed_msDel.count());
	}
	cout << "Search cuckoo method\n";
	for (int i = 0; i < max_len / 100 - 1; i++) {
		cout << CuckooMethodInsertStr[i] << ", ";
	}
	cout << "\nInsert cuckoo method\n";
	for (int i = 0; i < max_len / 100 - 1; i++) {
		cout << CuckooMethodSearchStr[i] << ", ";
	}
	cout << "\nDelete cuckoo method\n";
	for (int i = 0; i < max_len / 100 - 1; i++) {
		cout << CuckooMethodDeleteStr[i] << ", ";
	}


}