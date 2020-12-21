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
#include "../HashTable/DoubleHash.cpp"
#include "../HashTable/OpenAddressingLinearHash.cpp"
#include "../HashTable/OpenAddressingQuadraticHash.cpp"
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

int main()
{

	srand(time(0));
	const int max_len = 10000;
	const int step = 100;
	/*
	std::vector< int > OpenAddressingLinearInsertInt;
	std::vector< int > OpenAddressingLinearSearchInt;
	std::vector< int > OpenAddressingLinearDeleteInt;

	std::vector< int > OpenAddressingQuadraticInsertInt;
	std::vector< int > OpenAddressingQuadraticSearchInt;
	std::vector< int > OpenAddressingQuadraticDeleteInt;

	std::vector< int > OpenAddressingDoubleInsertInt;
	std::vector< int > OpenAddressingDoubleSearchInt;
	std::vector< int > OpenAddressingDoubleDeleteInt;

	std::vector< int > ChainingMethodInsertInt;
	std::vector< int > ChainingMethodSearchInt;
	std::vector< int > ChainingMethodDeleteInt;

	for (int k = 100; k < max_len; k = k+step){

		int a1 = distribution_a(gen);
		int b1 = distribution_b(gen);
		int a2 = distribution_a(gen);
		int b2 = distribution_b(gen);
		int size = k * 2;


		OpenAddressingLinearHash hash_table_OA(size, a1, b1);
		OpenAddressingQuadraticHash hash_table2_OA(nearest_pow2(k * 2), a1, b1);
		DoubleHash hash_table3_OA(nearest_pow2(k * 2), a1, b1, a2, b2);

		Hash_int hash_table_CM(k/3);

		for (int i = 0; i < k; i++){
			int val = 1 + rand() % 14742;
			hash_table_CM.insertItem(val);

			hash_table_OA.insertHash(val);
			hash_table2_OA.insertHash(val);
			hash_table3_OA.insertHash(val);


		}
		int value = 1 + rand() % 14742;

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
		auto beginInsertLin = std::chrono::steady_clock::now();
		hash_table_OA.insertHash(value);
		auto endInsertLin = std::chrono::steady_clock::now();
		auto elapsed_msInsertLin = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertLin - beginInsertLin);
		OpenAddressingLinearInsertInt.push_back(elapsed_msInsert.count());
		//quadratic
		auto beginInsertQ = std::chrono::steady_clock::now();
		hash_table2_OA.insertHash(value);
		auto endInsertQ = std::chrono::steady_clock::now();
		auto elapsed_msInsertQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertQ - beginInsertQ);
		OpenAddressingQuadraticInsertInt.push_back(elapsed_msInsertQ.count());
		//double
		auto beginInsertD = std::chrono::steady_clock::now();
		hash_table3_OA.insertHash(value);
		auto endInsertD = std::chrono::steady_clock::now();
		auto elapsed_msInsertD = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertD - beginInsertD);
		OpenAddressingDoubleInsertInt.push_back(elapsed_msInsertD.count());


		// ------SEARCH-------
		//linear
		auto beginSearchLin = std::chrono::steady_clock::now();
		hash_table_OA.search(value);
		auto endSearchLin = std::chrono::steady_clock::now();
		auto elapsed_msSearchLin = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchLin - beginSearchLin);
		OpenAddressingLinearSearchInt.push_back(elapsed_msSearch.count());
		//quadratic
		auto beginSearchQ = std::chrono::steady_clock::now();
		hash_table2_OA.search(value);
		auto endSearchQ = std::chrono::steady_clock::now();
		auto elapsed_msSearchQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchQ - beginSearchQ);
		OpenAddressingQuadraticSearchInt.push_back(elapsed_msSearchQ.count());
		//double
		auto beginSearchD = std::chrono::steady_clock::now();
		hash_table3_OA.search(value);
		auto endSearchD = std::chrono::steady_clock::now();
		auto elapsed_msSearchD = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchD - beginSearchD);
		OpenAddressingDoubleSearchInt.push_back(elapsed_msSearchD.count());


		// -----DELETE--------
		//linear
		auto beginDelete = std::chrono::steady_clock::now();
		hash_table_OA.deleteHash(value);
		auto endDelete = std::chrono::steady_clock::now();
		auto elapsed_msDelete = std::chrono::duration_cast<std::chrono::nanoseconds>(endDelete - beginDelete);
		OpenAddressingLinearDeleteInt.push_back(elapsed_msDelete.count());
		//quadratic
		auto beginDeleteQ = std::chrono::steady_clock::now();
		hash_table2_OA.deleteHash(value);
		auto endDeleteQ = std::chrono::steady_clock::now();
		auto elapsed_msDeleteQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteQ - beginDeleteQ);
		OpenAddressingQuadraticDeleteInt.push_back(elapsed_msDeleteQ.count());
		//double
		auto beginDeleteD = std::chrono::steady_clock::now();
		hash_table3_OA.deleteHash(value);
		auto endDeleteD = std::chrono::steady_clock::now();
		auto elapsed_msDeleteD = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteD - beginDeleteD);
		OpenAddressingDoubleDeleteInt.push_back(elapsed_msDeleteD.count());





	}
	cout<<"Search chaining method\n";
	for (int i = 0; i < max_len/100 - 1; i++){
		cout<<ChainingMethodInsertInt[i]<<' ';
	}
	cout<<"\nInsert chaining method\n";
	for (int i = 0; i < max_len/100 - 1; i++){
		cout<<ChainingMethodSearchInt[i]<<' ';
	}
	cout<<"\nDelete chaining method\n";
	for (int i = 0; i < max_len/100 - 1; i++){
		cout<<ChainingMethodDeleteInt[i]<<' ';
	}

	cout << endl;
	cout << "Insert (Linear,Qudratic,Double) INT" << endl;
	for (int i = 0; i < OpenAddressingLinearInsertInt.size(); ++i)
		std::cout << OpenAddressingLinearInsertInt[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticInsertInt.size(); ++i)
		std::cout << OpenAddressingQuadraticInsertInt[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleInsertInt.size(); ++i)
		std::cout << OpenAddressingDoubleInsertInt[i] << ' ';
	cout << endl << endl;

	cout << "Isearch (Linear,Qudratic,Double) INT" << endl;
	for (int i = 0; i < OpenAddressingLinearSearchInt.size(); ++i)
		std::cout << OpenAddressingLinearSearchInt[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticSearchInt.size(); ++i)
		std::cout << OpenAddressingQuadraticSearchInt[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleSearchInt.size(); ++i)
		std::cout << OpenAddressingDoubleSearchInt[i] << ' ';
	cout << endl << endl;

	cout << "Delete (Linear,Qudratic,Double) INT" << endl;
	for (int i = 0; i < OpenAddressingLinearDeleteInt.size(); ++i)
		std::cout << OpenAddressingLinearDeleteInt[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticDeleteInt.size(); ++i)
		std::cout << OpenAddressingQuadraticDeleteInt[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleDeleteInt.size(); ++i)
		std::cout << OpenAddressingDoubleDeleteInt[i] << ' ';
	cout << endl << endl;
	*/

	std::vector< int > OpenAddressingLinearInsertStr;
	std::vector< int > OpenAddressingLinearSearchStr;
	std::vector< int > OpenAddressingLinearDeleteStr;

	std::vector< int > OpenAddressingQuadraticInsertStr;
	std::vector< int > OpenAddressingQuadraticSearchStr;
	std::vector< int > OpenAddressingQuadraticDeleteStr;

	std::vector< int > OpenAddressingDoubleInsertStr;
	std::vector< int > OpenAddressingDoubleSearchStr;
	std::vector< int > OpenAddressingDoubleDeleteStr;

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

		OpenAddressingLinearHashStr hash_table(size, a1, b1);
		OpenAddressingQuadraticHashStr hash_table2(nearest_pow2(k), a1, b1);
		DoubleHashStr hash_table3(nearest_pow2(k), a1, a2);


		for (int i = 0; i < k; i++) {
			int len_string = 1 + rand() % 10;
			string str = gen_string(len_string);
			hash_table.insertHash(str);
			hash_table2.insertHash(str);
			hash_table3.insertHash(str);
		}
		int len_string = 1 + rand() % 10;
		string str = gen_string(len_string);

		// ------INSERT-------
		   //linear
		auto beginInsert = std::chrono::steady_clock::now();
		hash_table.insertHash(str);
		auto endInsert = std::chrono::steady_clock::now();
		auto elapsed_msInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - beginInsert);
		cout << elapsed_msInsert.count() << " nanoseconds" << endl;
		OpenAddressingLinearInsertStr.push_back(elapsed_msInsert.count());
		//quadratic
		auto beginInsertQ = std::chrono::steady_clock::now();
		hash_table2.insertHash(str);
		auto endInsertQ = std::chrono::steady_clock::now();
		auto elapsed_msInsertQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertQ - beginInsertQ);
		cout << elapsed_msInsertQ.count() << " nanoseconds" << endl;
		OpenAddressingQuadraticInsertStr.push_back(elapsed_msInsertQ.count());
		//double
		auto beginInsertD = std::chrono::steady_clock::now();
		hash_table3.insertHash(str);
		auto endInsertD = std::chrono::steady_clock::now();
		auto elapsed_msInsertD = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertD - beginInsertD);
		cout << elapsed_msInsertD.count() << " nanoseconds" << endl;
		OpenAddressingDoubleInsertStr.push_back(elapsed_msInsertD.count());


		// ------SEARCH-------
		  //linear
		auto beginSearch = std::chrono::steady_clock::now();
		hash_table.search(str);
		auto endSearch = std::chrono::steady_clock::now();
		auto elapsed_msSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - beginSearch);
		cout << elapsed_msSearch.count() << " nanoseconds" << endl;
		OpenAddressingLinearSearchStr.push_back(elapsed_msSearch.count());
		//quadratic
		auto beginSearchQ = std::chrono::steady_clock::now();
		hash_table2.search(str);
		auto endSearchQ = std::chrono::steady_clock::now();
		auto elapsed_msSearchQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchQ - beginSearchQ);
		cout << elapsed_msSearchQ.count() << " nanoseconds" << endl;
		OpenAddressingQuadraticSearchStr.push_back(elapsed_msSearchQ.count());
		//double
		auto beginSearchD = std::chrono::steady_clock::now();
		hash_table3.search(str);
		auto endSearchD = std::chrono::steady_clock::now();
		auto elapsed_msSearchD = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchD - beginSearchD);
		cout << elapsed_msSearchD.count() << " nanoseconds" << endl;
		OpenAddressingDoubleSearchStr.push_back(elapsed_msSearchD.count());


		// -----DELETE--------
		  //linear
		auto beginDelete = std::chrono::steady_clock::now();
		hash_table.deleteHash(str);
		auto endDelete = std::chrono::steady_clock::now();
		auto elapsed_msDelete = std::chrono::duration_cast<std::chrono::nanoseconds>(endDelete - beginDelete);
		cout << elapsed_msDelete.count() << " nanoseconds" << endl;
		OpenAddressingLinearDeleteStr.push_back(elapsed_msDelete.count());
		//quadratic
		auto beginDeleteQ = std::chrono::steady_clock::now();
		hash_table2.deleteHash(str);
		auto endDeleteQ = std::chrono::steady_clock::now();
		auto elapsed_msDeleteQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteQ - beginDeleteQ);
		cout << elapsed_msDeleteQ.count() << " nanoseconds" << endl;
		OpenAddressingQuadraticDeleteStr.push_back(elapsed_msDeleteQ.count());
		//double
		auto beginDeleteD = std::chrono::steady_clock::now();
		hash_table3.deleteHash(str);
		auto endDeleteD = std::chrono::steady_clock::now();
		auto elapsed_msDeleteD = std::chrono::duration_cast<std::chrono::nanoseconds>(endDeleteD - beginDeleteD);
		cout << elapsed_msDeleteD.count() << " nanoseconds" << endl;
		OpenAddressingDoubleDeleteStr.push_back(elapsed_msDeleteD.count());

		cout << endl;
	}



	cout << "Insert (Linear,Qudratic,Double) String" << endl;
	for (int i = 0; i < OpenAddressingLinearInsertStr.size(); ++i)
		std::cout << OpenAddressingLinearInsertStr[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticInsertStr.size(); ++i)
		std::cout << OpenAddressingQuadraticInsertStr[i] << ' ';
	cout << endl;
	for (int i = 0; i < OpenAddressingDoubleInsertStr.size(); ++i)
		std::cout << OpenAddressingDoubleInsertStr[i] << ' ';
	cout << endl << endl;

	cout << "Search (Linear,Qudratic,Double) String" << endl;
	for (int i = 0; i < OpenAddressingLinearSearchStr.size(); ++i)
		std::cout << OpenAddressingLinearSearchStr[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticSearchStr.size(); ++i)
		std::cout << OpenAddressingQuadraticSearchStr[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleSearchStr.size(); ++i)
		std::cout << OpenAddressingDoubleSearchStr[i] << ' ';
	cout << endl << endl;

	cout << "Delete (Linear,Qudratic,Double) String" << endl;
	for (int i = 0; i < OpenAddressingLinearDeleteStr.size(); ++i)
		std::cout << OpenAddressingLinearDeleteStr[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingQuadraticDeleteStr.size(); ++i)
		std::cout << OpenAddressingQuadraticDeleteStr[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < OpenAddressingDoubleDeleteStr.size(); ++i)
		std::cout << OpenAddressingDoubleDeleteStr[i] << ' ';
	cout << endl << endl;

	return 0;
}
