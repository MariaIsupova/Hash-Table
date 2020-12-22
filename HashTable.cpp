// Example program
#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <ctime>
#include <vector>
#include <stdio.h> 
#include <time.h>
#include <chrono>
#include "DoubleHash.cpp"
#include "OpenAddressingLinearHash.cpp"
#include "OpenAddressingQuadraticHash.cpp"
#include "ChainHash.cpp"
#include "CuckooHashing.cpp"
#include <fstream>

// for real data
#include <algorithm>
#include <sstream>

using namespace std;
using namespace std::chrono;


unsigned int nearest_pow2(unsigned int k)
{
	cout << " ";
	int nearest = 1;
	while (nearest <= k)
		nearest = nearest * 2;
	return nearest;
}

char chars[26];


string gen_string(int len_string) {
	string str;
	for (int l = 0; l <= len_string; l++) {
		str += chars[0 + rand() % 25];
	}
	return str;
}

vector<string> parsing_text() {
	string text = "";
	ifstream in("test.txt");

	if (!in.fail())
	{
		while (!in.eof()) text += in.get();
		in.close();
	}
	else cout << "file not found" << endl;

	string word;
	istringstream iss(text, istringstream::in);
	vector<string> wordsVector;
	while (iss >> word)
		wordsVector.push_back(word);
	reverse(begin(wordsVector), end(wordsVector));

	return wordsVector;
}

int main()
{
	srand(time(0));
	const int max_len = 50000;
	const int step = 500;  

	vector< int > OpenAddressingLinearInsertInt;
	vector< int > OpenAddressingLinearSearchInt;
	vector< int > OpenAddressingLinearDeleteInt;

	vector< int > OpenAddressingQuadraticInsertInt;
	vector< int > OpenAddressingQuadraticSearchInt;
	vector< int > OpenAddressingQuadraticDeleteInt;

	vector< int > OpenAddressingDoubleInsertInt;
	vector< int > OpenAddressingDoubleSearchInt;
	vector< int > OpenAddressingDoubleDeleteInt;

	vector< int > ChainingMethodInsertInt;
	vector< int > ChainingMethodSearchInt;
	vector< int > ChainingMethodDeleteInt;

	vector< int > CuckooMethodInsertInt;
	vector< int > CuckooMethodSearchInt;
	vector< int > CuckooMethodDeleteInt;

	   
	for (int k = 100; k <= max_len; k = k + step) {
		//cout << k << " elements " << "  nearest " << nearest_pow2(k * 2) << endl;

		int a1 = distribution_a(gen);
		int b1 = distribution_b(gen);
		int a2 = distribution_a(gen);
		int b2 = distribution_b(gen);
		int size = k * 2;

		Hash_int hash_table_CM(k / 3);
		OpenAddressingLinearHash hash_table(size, a1, b1);
		OpenAddressingQuadraticHash hash_table2(nearest_pow2(k * 2), a1, b1);
		DoubleHash hash_table3(nearest_pow2(k * 2), a1, b1, a2, b2);
		cuckoo hash_table_Cuckoo(k, 3);


		for (int i = 0; i < k; i++) {
			int val = 1 + rand() % 147483647;
			hash_table_CM.insertItem(val);
			hash_table.insertHash(val);
			hash_table2.insertHash(val);
			hash_table3.insertHash(val);
			hash_table_Cuckoo.insert(val);
		}
		int value = 1 + rand() % 147483647;

		// ------INSERT------- 
		auto beginInsert = std::chrono::steady_clock::now();
		hash_table_CM.insertItem(value);
		auto endInsert = std::chrono::steady_clock::now();
		auto elapsed_msInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - beginInsert);
		// ------SEARCH-------
		auto beginSearch = std::chrono::steady_clock::now();
		hash_table_CM.searchItem(value);
		auto endSearch = std::chrono::steady_clock::now();
		auto elapsed_msSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - beginSearch);
		// -----DELETE--------
		auto beginDel = std::chrono::steady_clock::now();
		hash_table_CM.deleteItem(value);
		auto endDel = std::chrono::steady_clock::now();
		auto elapsed_msDel = std::chrono::duration_cast<std::chrono::nanoseconds>(endDel - beginDel);



		ChainingMethodInsertInt.push_back(elapsed_msInsert.count());
		ChainingMethodSearchInt.push_back(elapsed_msSearch.count());
		ChainingMethodDeleteInt.push_back(elapsed_msDel.count());

		// ------INSERT-------
		   //linear
		auto beginInsert = std::chrono::steady_clock::now();
		hash_table.insertHash(value);
		auto endInsert = std::chrono::steady_clock::now();
		auto elapsed_msInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - beginInsert);
		OpenAddressingLinearInsertInt.push_back(elapsed_msInsert.count());
		//quadratic
		auto beginInsertQ = std::chrono::steady_clock::now();
		hash_table2.insertHash(value);
		auto endInsertQ = std::chrono::steady_clock::now();
		auto elapsed_msInsertQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertQ - beginInsertQ);
		OpenAddressingQuadraticInsertInt.push_back(elapsed_msInsertQ.count());
		//double
		auto beginInsertD = std::chrono::steady_clock::now();
		hash_table3.insertHash(value);
		auto endInsertD = std::chrono::steady_clock::now();
		auto elapsed_msInsertD = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertD - beginInsertD);
		OpenAddressingDoubleInsertInt.push_back(elapsed_msInsertD.count());


		// ------SEARCH-------
		  //linear
		auto beginSearch = std::chrono::steady_clock::now();
		hash_table.search(value);
		auto endSearch = std::chrono::steady_clock::now();
		auto elapsed_msSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - beginSearch);
		OpenAddressingLinearSearchInt.push_back(elapsed_msSearch.count());
		//quadratic
		auto beginSearchQ = std::chrono::steady_clock::now();
		hash_table2.search(value);
		auto endSearchQ = std::chrono::steady_clock::now();
		auto elapsed_msSearchQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchQ - beginSearchQ);
		OpenAddressingQuadraticSearchInt.push_back(elapsed_msSearchQ.count());
		//double
		auto beginSearchD = std::chrono::steady_clock::now();
		hash_table3.search(value);
		auto endSearchD = std::chrono::steady_clock::now();
		auto elapsed_msSearchD = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchD - beginSearchD);
		OpenAddressingDoubleSearchInt.push_back(elapsed_msSearchD.count());


		// -----DELETE--------
		  //linear
		auto beginDelete = std::chrono::steady_clock::now();
		hash_table.deleteHash(value);
		auto endDelete = std::chrono::steady_clock::now();
		auto elapsed_msDelete = std::chrono::duration_cast<std::chrono::nanoseconds>(endDelete - beginDelete);
		OpenAddressingLinearDeleteInt.push_back(elapsed_msDelete.count());
		//quadratic
		auto beginDeleteQ = std::chrono::steady_clock::now();
		hash_table2.deleteHash(value);
		auto endDeleteQ = std::chrono::steady_clock::now();
		auto elapsed_msDeleteQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteQ - beginDeleteQ);
		OpenAddressingQuadraticDeleteInt.push_back(elapsed_msDeleteQ.count());
		//double
		auto beginDeleteD = std::chrono::steady_clock::now();
		hash_table3.deleteHash(value);
		auto endDeleteD = std::chrono::steady_clock::now();
		auto elapsed_msDeleteD = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteD - beginDeleteD);
		OpenAddressingDoubleDeleteInt.push_back(elapsed_msDeleteD.count());


		// ------INSERT-------Cuckoo
		auto beginInsert = std::chrono::steady_clock::now();
		hash_table_Cuckoo.insert(value);
		auto endInsert = std::chrono::steady_clock::now();
		auto elapsed_msInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - beginInsert);
		// ------SEARCH-------Cuckoo
		auto beginSearch = std::chrono::steady_clock::now();
		hash_table_Cuckoo.search(value);
		auto endSearch = std::chrono::steady_clock::now();
		auto elapsed_msSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - beginSearch);
		// -----DELETE--------Cuckoo
		auto beginDel = std::chrono::steady_clock::now();
		hash_table_Cuckoo.Delete(value);
		auto endDel = std::chrono::steady_clock::now();
		auto elapsed_msDel = std::chrono::duration_cast<std::chrono::nanoseconds>(endDel - beginDel);

		cout << endl;
	}

	cout << "Search chaining method\n";
	for (int i = 0; i < max_len / 100 - 1; i++) 
		cout << ChainingMethodInsertInt[i] << ", ";
	cout << endl << endl;
	cout << "\nInsert chaining method\n";
	for (int i = 0; i < max_len / 100 - 1; i++) 
		cout << ChainingMethodSearchInt[i] << ", ";
	cout << endl << endl;
	cout << "\nDelete chaining method\n";
	for (int i = 0; i < max_len / 100 - 1; i++) 
		cout << ChainingMethodDeleteInt[i] << ", ";
	cout << endl << endl;

	cout << "Insert (Linear,Qudratic,Double) INT" << endl;
	for (int i = 0; i < OpenAddressingLinearInsertInt.size(); ++i)
		std::cout << OpenAddressingLinearInsertInt[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticInsertInt.size(); ++i)
		std::cout << OpenAddressingQuadraticInsertInt[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleInsertInt.size(); ++i)
		std::cout << OpenAddressingDoubleInsertInt[i] << ",";
	cout << endl << endl;
	cout << "Isearch (Linear,Qudratic,Double) INT" << endl;
	for (int i = 0; i < OpenAddressingLinearSearchInt.size(); ++i)
		std::cout << OpenAddressingLinearSearchInt[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticSearchInt.size(); ++i)
		std::cout << OpenAddressingQuadraticSearchInt[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleSearchInt.size(); ++i)
		std::cout << OpenAddressingDoubleSearchInt[i] << ",";
	cout << endl << endl;

	cout << "Delete (Linear,Qudratic,Double) INT" << endl;
	for (int i = 0; i < OpenAddressingLinearDeleteInt.size(); ++i)
		std::cout << OpenAddressingLinearDeleteInt[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticDeleteInt.size(); ++i)
		std::cout << OpenAddressingQuadraticDeleteInt[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleDeleteInt.size(); ++i)
		std::cout << OpenAddressingDoubleDeleteInt[i] << ",";
	cout << endl << endl;
	cout << "Search cuckoo method\n";
	for (int i = 0; i < max_len / 100 - 1; i++) 
		cout << CuckooMethodInsertInt[i] << ' ';
	cout << endl << endl;
	cout << "\nInsert cuckoo method\n";
	for (int i = 0; i < max_len / 100 - 1; i++) 
		cout << CuckooMethodSearchInt[i] << ' ';
	cout << endl << endl;
	cout << "\nDelete cuckoo method\n";
	for (int i = 0; i < max_len / 100 - 1; i++) 
		cout << CuckooMethodDeleteInt[i] << ' ';
	
	

	// String
	for (int i = 97, n = 0; i <= 122; ++i, ++n)
	{
		chars[n] = (char)i;
	}
	
	vector< int > OpenAddressingLinearInsertStr;
	vector< int > OpenAddressingLinearSearchStr;
	vector< int > OpenAddressingLinearDeleteStr;

	vector< int > OpenAddressingQuadraticInsertStr;
	vector< int > OpenAddressingQuadraticSearchStr;
	vector< int > OpenAddressingQuadraticDeleteStr;

	vector< int > OpenAddressingDoubleInsertStr;
	vector< int > OpenAddressingDoubleSearchStr;
	vector< int > OpenAddressingDoubleDeleteStr;

	vector< int > ChainingMethodInsertStr;
	vector< int > ChainingMethodSearchStr;
	vector< int > ChainingMethodDeleteStr;

	vector< int > InsertStr;
	vector< int > SearchStr;
	vector< int > DeleteStr;

	srand(time(NULL));
	for (int i = 97, n = 0; i <= 122; ++i, ++n)
	{
		chars[n] = (char)i;
	}

	for (int k = 100; k <= max_len; k = k + step) {
		cout << k << " elements " << endl;
		int p = 15001;
		std::mt19937 gen(time(0)); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> distribution_a(1, p - 1);
		std::uniform_int_distribution<> distribution_b(0, p - 1);
		int a1 = distribution_a(gen);
		int b1 = distribution_b(gen);
		int a2 = distribution_a(gen);
		int b2 = distribution_b(gen);
		int size = k * 2;

		Hash_string hash_table_CM_str(k / 3);
		OpenAddressingLinearHashStr hash_table(size, a1, b1);
		OpenAddressingQuadraticHashStr hash_table2(nearest_pow2(k), a1, b1);
		DoubleHashStr hash_table3(nearest_pow2(k), a1, a2);


		for (int i = 0; i < k; i++) {
			int len_string = 1 + rand() % 10;
			string str = gen_string(len_string);
			hash_table_CM_str.insertItem(str);
			hash_table.insertHash(str);
			hash_table2.insertHash(str);
			hash_table3.insertHash(str);
		}
		int len_string = 1 + rand() % 10;
		string str = gen_string(len_string);

		// ------INSERT------- 
		auto beginInsert = std::chrono::steady_clock::now();
		hash_table_CM_str.insertItem(str);
		auto endInsert = std::chrono::steady_clock::now();
		auto elapsed_msInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - beginInsert);
		// ------SEARCH-------
		auto beginSearch = std::chrono::steady_clock::now();
		hash_table_CM_str.searchItem(str);
		auto endSearch = std::chrono::steady_clock::now();
		auto elapsed_msSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - beginSearch);
		// -----DELETE--------
		auto beginDel = std::chrono::steady_clock::now();
		hash_table_CM_str.deleteItem(str);
		auto endDel = std::chrono::steady_clock::now();
		auto elapsed_msDel = std::chrono::duration_cast<std::chrono::nanoseconds>(endDel - beginDel);


		ChainingMethodInsertStr.push_back(elapsed_msInsert.count());
		ChainingMethodSearchStr.push_back(elapsed_msSearch.count());
		ChainingMethodDeleteStr.push_back(elapsed_msDel.count());


		// ------INSERT-------OpenAddressing
		   //linear
		auto beginInsert = std::chrono::steady_clock::now();
		hash_table.insertHash(str);
		auto endInsert = std::chrono::steady_clock::now();
		auto elapsed_msInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - beginInsert);
		OpenAddressingLinearInsertStr.push_back(elapsed_msInsert.count());
		//quadratic
		auto beginInsertQ = std::chrono::steady_clock::now();
		hash_table2.insertHash(str);
		auto endInsertQ = std::chrono::steady_clock::now();
		auto elapsed_msInsertQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertQ - beginInsertQ);
		OpenAddressingQuadraticInsertStr.push_back(elapsed_msInsertQ.count());
		//double
		auto beginInsertD = std::chrono::steady_clock::now();
		hash_table3.insertHash(str);
		auto endInsertD = std::chrono::steady_clock::now();
		auto elapsed_msInsertD = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertD - beginInsertD);
		OpenAddressingDoubleInsertStr.push_back(elapsed_msInsertD.count());


		// ------SEARCH-------
		  //linear
		auto beginSearch = std::chrono::steady_clock::now();
		hash_table.search(str);
		auto endSearch = std::chrono::steady_clock::now();
		auto elapsed_msSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - beginSearch);
		OpenAddressingLinearSearchStr.push_back(elapsed_msSearch.count());
		  //quadratic
		auto beginSearchQ = std::chrono::steady_clock::now();
		hash_table2.search(str);
		auto endSearchQ = std::chrono::steady_clock::now();
		auto elapsed_msSearchQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchQ - beginSearchQ);
		OpenAddressingQuadraticSearchStr.push_back(elapsed_msSearchQ.count());
		//double
	    auto beginSearchD = std::chrono::steady_clock::now();
		hash_table3.search(str);
		auto endSearchD = std::chrono::steady_clock::now();
		auto elapsed_msSearchD = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchD - beginSearchD);
		OpenAddressingDoubleSearchStr.push_back(elapsed_msSearchD.count());


		// -----DELETE--------
		  //linear
		auto beginDelete = std::chrono::steady_clock::now();
		hash_table.deleteHash(str);
		auto endDelete = std::chrono::steady_clock::now();
		auto elapsed_msDelete = std::chrono::duration_cast<std::chrono::nanoseconds>(endDelete - beginDelete);
		OpenAddressingLinearDeleteStr.push_back(elapsed_msDelete.count());
		  //quadratic
		auto beginDeleteQ = std::chrono::steady_clock::now();
		hash_table2.deleteHash(str);
		auto endDeleteQ = std::chrono::steady_clock::now();
		auto elapsed_msDeleteQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteQ - beginDeleteQ);
		OpenAddressingQuadraticDeleteStr.push_back(elapsed_msDeleteQ.count());
		  //double
		auto beginDeleteD = std::chrono::steady_clock::now();
		hash_table3.deleteHash(str);
		auto endDeleteD = std::chrono::steady_clock::now();
		auto elapsed_msDeleteD = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteD - beginDeleteD);

		OpenAddressingDoubleDeleteStr.push_back(elapsed_msDeleteD.count());

		cout << endl;




	}

	cout << "Search chaining method for string\n";
	for (int i = 0; i < max_len / 100 - 1; i++) 
		cout << ChainingMethodInsertStr[i] << ", ";
	cout << endl << endl;
	cout << "\nInsert chaining method for string\n";
	for (int i = 0; i < max_len / 100 - 1; i++) 
		cout << ChainingMethodSearchStr[i] << ", ";
	cout << endl << endl;
	cout << "\nDelete chaining method for string\n";
	for (int i = 0; i < max_len / 100 - 1; i++) 
		cout << ChainingMethodDeleteStr[i] << ", ";
	cout << endl << endl;

	cout << "Insert (Linear,Qudratic,Double) String" << endl;
	for (int i = 0; i < OpenAddressingLinearInsertStr.size(); ++i)
		std::cout << OpenAddressingLinearInsertStr[i] << "  ";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticInsertStr.size(); ++i)
		std::cout << OpenAddressingQuadraticInsertStr[i] << ",";
	cout << endl;
	for (int i = 0; i < OpenAddressingDoubleInsertStr.size(); ++i)
		std::cout << OpenAddressingDoubleInsertStr[i] << ",";
	cout << endl << endl;

	cout << "Search (Linear,Qudratic,Double) String" << endl;
	for (int i = 0; i < OpenAddressingLinearSearchStr.size(); ++i)
		std::cout << OpenAddressingLinearSearchStr[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticSearchStr.size(); ++i)
		std::cout << OpenAddressingQuadraticSearchStr[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleSearchStr.size(); ++i)
		std::cout << OpenAddressingDoubleSearchStr[i] << ",";
	cout << endl << endl;

	cout << "Delete (Linear,Qudratic,Double) String" << endl;
	for (int i = 0; i < OpenAddressingLinearDeleteStr.size(); ++i)
		std::cout << OpenAddressingLinearDeleteStr[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticDeleteStr.size(); ++i)
		std::cout << OpenAddressingQuadraticDeleteStr[i] << ",";
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleDeleteStr.size(); ++i)
		std::cout << OpenAddressingDoubleDeleteStr[i] << ",";
	cout << endl << endl;
	


    // Real data 37717

	vector< int > OpenAddressingLinearInsertData;
	vector< int > OpenAddressingLinearSearchData;
	vector< int > OpenAddressingLinearDeleteData;

	vector< int > OpenAddressingQuadraticInsertData;
	vector< int > OpenAddressingQuadraticSearchData;
	vector< int > OpenAddressingQuadraticDeleteData;

	vector< int > OpenAddressingDoubleInsertData;
	vector< int > OpenAddressingDoubleSearchData;
	vector< int > OpenAddressingDoubleDeleteData;

	vector< int > ChainingMethodInsertData;
	vector< int > ChainingMethodSearchData;
	vector< int > ChainingMethodDeleteData;

	vector< int > InsertData;
	vector< int > SearchData;
	vector< int > DeleteData;

	vector<string> text= parsing_text();
	//for (int i = 0; i < text.size(); ++i)
		//std::cout << text[i];

	for (int k = 0; k < text.size(); ++k) {
		string str = text[k];
		//cout << k << " elements " << endl;
		int p = 15001;
		std::mt19937 gen(time(0)); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> distribution_a(1, p - 1);
		std::uniform_int_distribution<> distribution_b(0, p - 1);
		int a1 = distribution_a(gen);
		int b1 = distribution_b(gen);
		int a2 = distribution_a(gen);
		int b2 = distribution_b(gen);
		int size = k * 2;

		Hash_string hash_table_CM_data(k / 3);
		OpenAddressingLinearHashStr hash_table_data(size, a1, b1);
		OpenAddressingQuadraticHashStr hash_table2_data(nearest_pow2(k), a1, b1);
		DoubleHashStr hash_table3_data(nearest_pow2(k), a1, a2);


		// ------INSERT------- 
		auto beginInsert = std::chrono::steady_clock::now();
		hash_table_CM_data.insertItem(str);
		auto endInsert = std::chrono::steady_clock::now();
		auto elapsed_msInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - beginInsert);


		// ------SEARCH-------
		auto beginSearch = std::chrono::steady_clock::now();
		hash_table_CM_data.searchItem(str);
		auto endSearch = std::chrono::steady_clock::now();
		auto elapsed_msSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - beginSearch);


		// -----DELETE--------
		auto beginDel = std::chrono::steady_clock::now();
		hash_table_CM_data.deleteItem(str);
		auto endDel = std::chrono::steady_clock::now();
		auto elapsed_msDel = std::chrono::duration_cast<std::chrono::nanoseconds>(endDel - beginDel);



		ChainingMethodInsertData.push_back(elapsed_msInsert.count());
		ChainingMethodSearchData.push_back(elapsed_msSearch.count());
		ChainingMethodDeleteData.push_back(elapsed_msDel.count());


		// ------INSERT-------OpenAddressing
		   //linear
		auto beginInsert = std::chrono::steady_clock::now();
		hash_table_data.insertHash(str);
		auto endInsert = std::chrono::steady_clock::now();
		auto elapsed_msInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - beginInsert);
		OpenAddressingLinearInsertData.push_back(elapsed_msInsert.count());
		//quadratic
		auto beginInsertQ = std::chrono::steady_clock::now();
		hash_table2_data.insertHash(str);
		auto endInsertQ = std::chrono::steady_clock::now();
		auto elapsed_msInsertQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertQ - beginInsertQ);
		OpenAddressingQuadraticInsertData.push_back(elapsed_msInsertQ.count());
		//double
		auto beginInsertD = std::chrono::steady_clock::now();
		hash_table3_data.insertHash(str);
		auto endInsertD = std::chrono::steady_clock::now();
		auto elapsed_msInsertD = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertD - beginInsertD);
		OpenAddressingDoubleInsertData.push_back(elapsed_msInsertD.count());


		// ------SEARCH-------
		  //linear
		auto beginSearch = std::chrono::steady_clock::now();
		hash_table_data.search(str);
		auto endSearch = std::chrono::steady_clock::now();
		auto elapsed_msSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - beginSearch);
		OpenAddressingLinearSearchData.push_back(elapsed_msSearch.count());
		//quadratic
		auto beginSearchQ = std::chrono::steady_clock::now();
		hash_table2_data.search(str);
		auto endSearchQ = std::chrono::steady_clock::now();
		auto elapsed_msSearchQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchQ - beginSearchQ);
		OpenAddressingQuadraticSearchData.push_back(elapsed_msSearchQ.count());
		//double
		auto beginSearchD = std::chrono::steady_clock::now();
		hash_table3_data.search(str);
		auto endSearchD = std::chrono::steady_clock::now();
		auto elapsed_msSearchD = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchD - beginSearchD);
		OpenAddressingDoubleSearchData.push_back(elapsed_msSearchD.count());


		// -----DELETE--------
		  //linear
		auto beginDelete = std::chrono::steady_clock::now();
		hash_table_data.deleteHash(str);
		auto endDelete = std::chrono::steady_clock::now();
		auto elapsed_msDelete = std::chrono::duration_cast<std::chrono::nanoseconds>(endDelete - beginDelete);
		OpenAddressingLinearDeleteData.push_back(elapsed_msDelete.count());
		//quadratic
		auto beginDeleteQ = std::chrono::steady_clock::now();
		hash_table2_data.deleteHash(str);
		auto endDeleteQ = std::chrono::steady_clock::now();
		auto elapsed_msDeleteQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteQ - beginDeleteQ);
		OpenAddressingQuadraticDeleteData.push_back(elapsed_msDeleteQ.count());
		//double
		auto beginDeleteD = std::chrono::steady_clock::now();
		hash_table3_data.deleteHash(str);
		auto endDeleteD = std::chrono::steady_clock::now();
		auto elapsed_msDeleteD = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteD - beginDeleteD);
		//cout << elapsed_msDeleteD.count() << " nanoseconds" << endl;
		OpenAddressingDoubleDeleteData.push_back(elapsed_msDeleteD.count());


	}

	cout << "Search chaining method for data\n";
	long long sum_ChainingMethodInsertData;
	for (int i = 0; i < ChainingMethodInsertData.size() - 1; i++)
		sum_ChainingMethodInsertData += ChainingMethodInsertData[i];
	cout<< sum_ChainingMethodInsertData / ChainingMethodInsertData.size()<< endl;

	long long sum_ChainingMethodSearchData;
	cout << "\nInsert chaining method for data\n";
	for (int i = 0; i < ChainingMethodSearchData.size(); i++)
		sum_ChainingMethodSearchData += ChainingMethodSearchData[i];
	cout << sum_ChainingMethodSearchData / ChainingMethodSearchData.size() << endl;

	long long sum_ChainingMethodDeleteData;
	cout << "\nDelete chaining method for data\n";
	for (int i = 0; i < ChainingMethodDeleteData.size(); i++)
		sum_ChainingMethodDeleteData += ChainingMethodDeleteData[i];
	cout << sum_ChainingMethodDeleteData / ChainingMethodDeleteData.size() << endl;


	cout << "Insert (Linear,Qudratic,Double) String" << endl;
	long long sum_OpenAddressingLinearInsertData;
	for (int i = 0; i < OpenAddressingLinearInsertData.size(); ++i)
		sum_OpenAddressingLinearInsertData += OpenAddressingLinearInsertData[i];
	cout << sum_OpenAddressingLinearInsertData / OpenAddressingLinearInsertData.size() << endl;

	long long sum_OpenAddressingQuadraticInsertData;
	for (int i = 0; i < OpenAddressingQuadraticInsertData.size(); ++i)
		sum_OpenAddressingQuadraticInsertData += OpenAddressingQuadraticInsertData[i];
	cout << sum_OpenAddressingQuadraticInsertData / OpenAddressingQuadraticInsertData.size() << endl;

	long long sum_OpenAddressingDoubleInsertData;
	for (int i = 0; i < OpenAddressingDoubleInsertData.size(); ++i)
		sum_OpenAddressingDoubleInsertData += OpenAddressingDoubleInsertData[i];
	cout << sum_OpenAddressingDoubleInsertData / OpenAddressingDoubleInsertData.size() << endl;


	cout << "Search (Linear,Qudratic,Double) String" << endl;
	long long sum_OpenAddressingLinearSearchData;
	for (int i = 0; i < OpenAddressingLinearSearchData.size(); ++i)
		sum_OpenAddressingLinearSearchData += OpenAddressingLinearSearchData[i];
	cout << sum_OpenAddressingLinearSearchData / OpenAddressingLinearSearchData.size() << endl;

	long long sum_OpenAddressingQuadraticSearchData;
	for (int i = 0; i < OpenAddressingQuadraticSearchData.size(); ++i)
		sum_OpenAddressingQuadraticSearchData += OpenAddressingQuadraticSearchData[i];
	cout << sum_OpenAddressingQuadraticSearchData / OpenAddressingQuadraticSearchData.size() << endl;

	long long sum_OpenAddressingDoubleSearchData;
	for (int i = 0; i < OpenAddressingDoubleSearchData.size(); ++i)
		sum_OpenAddressingDoubleSearchData += OpenAddressingDoubleSearchData[i];
	cout << sum_OpenAddressingDoubleSearchData / OpenAddressingDoubleSearchData.size() << endl;

	cout << "Delete (Linear,Qudratic,Double) String" << endl;
	long long sum_OpenAddressingLinearDeleteData;
	for (int i = 0; i < OpenAddressingLinearDeleteData.size(); ++i)
		sum_OpenAddressingLinearDeleteData += OpenAddressingLinearDeleteData[i];
	cout << sum_OpenAddressingLinearDeleteData / OpenAddressingLinearDeleteData.size() << endl;

	long long sum_OpenAddressingQuadraticDeleteData;
	for (int i = 0; i < OpenAddressingQuadraticDeleteData.size(); ++i)
		sum_OpenAddressingQuadraticDeleteData += OpenAddressingQuadraticDeleteData[i];
	cout << sum_OpenAddressingQuadraticDeleteData / OpenAddressingQuadraticDeleteData.size() << endl;

	long long sum_OpenAddressingDoubleDeleteData;
	for (int i = 0; i < OpenAddressingDoubleDeleteData.size(); ++i)
		sum_OpenAddressingDoubleDeleteData += OpenAddressingDoubleDeleteData[i];
	cout << sum_OpenAddressingDoubleDeleteData / OpenAddressingDoubleDeleteData.size() << endl;

	return 0;
}
