#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<cmath>
#include<string>
#include<vector>
#include<iterator>
#include<chrono>
#include "func.h"
int main(int argc, char* argv[]) {
	string infile="hotels1k.csv";//open this file "hotels1k.csv" by default

	for (int i = 0; i < argc; i++) {//get the input file from the prompt
		if (string(argv[i]) == "-f" && i + 1 < argc)
			infile = argv[i + 1];
	}


	ifstream fin1;
	fin1.open(infile);
	if (!fin1) {
		cout << "Can not open the file...!";
		exit(-1);
	}
	string check;
	int size_cnt=0;//this is to count the size of the file so that we can initialize hashmaps with proper size
	while (!fin1.eof()) {
		getline(fin1, check);
		size_cnt++;
	}
	size_cnt = int(size_cnt * 1.334);
	while (not is_prime(size_cnt)) {// Prime number bigger than > size*1.334;
		size_cnt++;
	}

	ifstream fin;
	fin.open(infile);
	string line;
	HashMap1 myHashMap1(size_cnt);//initialize hashmap 1 with size of the prime we get
	HashMap2 myHashMap2(size_cnt);//initialize hashmap 2 with size of the prime we get, hashmap 2 is to realize allincity function
	getline(fin, line);  //skip first line
	while (!fin.eof())
	{
		string *value1 = new string[4];//array to contain "star", "price", "country name", "address"
		string *value2 = new string[5];//array to contain "hotel name", "star", "price", "country name", "address"
		string key1, key2;
		getline(fin, key1, ',');
		getline(fin, key2, ',');
		for (int i = 0; i < 3; i++) {//create value1 from the input
			getline(fin, value1[i],',');
		}
		getline(fin, value1[3]);
		value2[0] = key1;//create value2 from the input
		for (int j = 0; j < 4; j++) {//value2 has same variables as value1 but with one more entry of "hotel name"
			value2[j + 1] = value1[j];
		}
		cout << key1 << "," << key2<< endl;//display "hotel name", "city name"
		myHashMap1.add(key1 +","+ key2, value1);//insert the node into map1 with key as combination of "hotel name", "city name"
		myHashMap2.add(key2, value2);//insert the node into map2 with key as just "city name"
	}
	cout << "Hash Map size = " << myHashMap1.getSize() <<endl;//print the size of the map
	fin.close();

    
	while (true) {
        string command,choice;
		string input[6] = { "hotel name", "city name", "star", "price", "country name", "address" };
		cout << "\nPlease input your command appropriately and accordingly\n<find add delete dump allinCity quit>" << endl;//function menu
		getline(cin, choice);
		stringstream input_stringstream(choice);
		size_t found = choice.find(' ');
		if (found!= string::npos){ //if there is space, then consider first word as command
			getline(input_stringstream, command, ' ');//get the command
		}
		else {//otherwise consider the whole string as a command
			command = choice;
		}
		if (command == "find") {//finding
			string findkey;//expecting combination of hotel name and city name seperated by a comma
            int comparison = 0;
			getline(input_stringstream, findkey);
			auto start = chrono::steady_clock::now();//start measuring the execution time
			if (myHashMap1.find(findkey,comparison) != nullptr) {//find function returned a node
				auto end = chrono::steady_clock::now();//end measuring the execution time
				cout << "hotel found" << endl;
				cout << "-----------------" << endl;
				cout << findkey << endl;
				for (int i = 0; i < 4; i++) {//print the information of found hotel
					cout << input[i + 2] << ": " << myHashMap1.find(findkey, comparison)[i] << endl;
				}
				cout << "-----------------" << endl;
				cout << comparison <<" comparison carried out"<<endl;
				auto diff = end - start;
				cout <<"execution time: "<< chrono::duration <double, milli>(diff).count() << " ms" << endl;//print execution time in miliseconds
			}
			else {//find function returns nullptr
				cout << "no such hotel in such city found" << endl;
			}

		}
		else if (command == "add") {//inserting
			string output[6];//array to contain the inserted information
			for (int i = 0; i < 5; i++) {
				getline(input_stringstream,output[i],',');//information is inputed as string with comma as delimiter
			} 
			getline(input_stringstream, output[5]);
			string *v = new string[4];//value1 to be put in hashmap1
			string *y = new string[5];//value2 to be put in hashmap2
			y[0] = output[0];
			for (int i = 0; i < 4; i++) {
				v[i] = output[i+2];
				y[i + 1] = v[i];
			}
			myHashMap1.add(output[0] + "," + output[1], v);//output[0] +","+ output[1] is combinatino of hotel name and city name
			myHashMap2.add(output[1], y);//output[1] is city name
		}
		else if (command == "delete") {//deleting
			string findkey,city,hotel;
			int comparison = 0; 
			getline(input_stringstream, hotel,',');
			getline(input_stringstream, city);
			findkey = hotel + ',' + city;//findkey as combination of hotel name and city name
			if (myHashMap1.find(findkey,comparison) != nullptr) {
				myHashMap1.remove(findkey);//delete found node in hashmap1 
				myHashMap2.remove(city, hotel);//delete found node in hashmap1
				cout << "hotel found and already deleted" << endl;
				cout << comparison << " comparison carried out" << endl;
			}
			else {
				cout << "no such hotel in such city found" << endl;
			}
		}
		else if (command == "dump") {//sort and dump
			cout << "size of the sorting machine: " << myHashMap1.sort_hotel().size() << endl;
			string filename;
			getline(input_stringstream, filename);
			ofstream myfile;
			myfile.open(filename + ".txt");
			myfile << "hotelName,cityName,stars,price,countryName,address\n";//write the first line
			vector<string> sort_machine = myHashMap1.sort_hotel();//get the sorted vector containing every hotel
			for (int i = 0; i < sort_machine.size(); i++) {//dump each string in the sorting machine to the file
				myfile << sort_machine[i]+"\n";
			}
			myfile.close();
			cout << "sorted hotels have been dumped to the file" << endl;

		}
		else if (command == "allinCity") {//allincity
			string city;
			getline(input_stringstream, city);
			myHashMap2.listall(city);//print all hotels in the city from hashmap2
		}
		else if (command == "quit") {
			cout << "wow Im terminating" << endl;
			break;//exit the while loop to exit
		}
		else {//detect wrong input
			cout <<"here is your command: " <<command << endl;
			cout<<"see, its a wrong input"<<endl;
			cout << "check if you have space before comma or any other typos:)" << endl;
		}
	}
	return 0;
}
