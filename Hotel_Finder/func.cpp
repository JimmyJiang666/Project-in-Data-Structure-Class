#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<string>
#include<vector>
#include<iterator>
#include"func.h"

using namespace std;

HashNode::HashNode(string key, string* value) : key(key), value(value) {}//constructor for the node
string HashNode::getKey() { return this->key; }
string* HashNode::getValue() { return this->value; }
HashNode::~HashNode() { delete[] this->value; }

HashMap1::HashMap1(int capacity) :capacity(capacity), size(0) {//constructor for the hashmap1
	nodearray = new HashNode*[capacity];
}

unsigned long HashMap1::hashCode(string key){//hashcode for the input key
	unsigned long sum = 0;
	for (int i = 0; i < key.length(); i++)
		sum += key[i] * pow(i, 10);
	return sum;
}

void HashMap1::add(string key, string* value) {
	unsigned long index = hashCode(key) % capacity;//hashnode modulo capacity of array
	while (nodearray[index] != NULL) {//if the position is already occupied
		if (nodearray[index]->getKey() == key) {//repetitive error if input key already existed in the map
			cout << "repetitive error" << endl;
			return;
		}
		else if (nodearray[index]->getKey() == "available") {//"available" is the placeholder after remove function
			nodearray[index] = new HashNode(key, value);
			size++;
			return;
		}
		else {//do linear probing to next index
			index = (index + 1) % capacity;
		}
	}
	nodearray[index] = new HashNode(key, value);//put the input node in the map
	size++;//increase size of the map
}

string* HashMap1::find(string key, int& comparison) {//find the hashnode and output comparison
	int index = hashCode(key) % capacity;//modulo the size of array
	int cnt = 0;//counter for the comparison time
	while (cnt < capacity) {//stop if we iterate the whole array
		if (nodearray[index] != NULL && nodearray[index]->getKey() == key) {//if the keys match
			comparison = cnt + 1;
			return nodearray[index]->getValue();//return the found hashnode
		}
		index = (index + 1) % capacity;//not found, move to the next hashnode
		cnt++;//update comparison counter
	}
	return nullptr;
}

int HashMap1::findindex(string key) {//similar find function to get index
	unsigned long index = hashCode(key) % capacity;
	int cnt = 0;//counter how many comparison we done
	while (cnt < capacity) {//if we haven't iterate the whole array
		if (nodearray[index] != NULL && nodearray[index]->getKey() == key) {
			return index;
		}
		index = (index + 1) % capacity;//not found, move to the next index
		cnt++;
	}
	return -1;
}

void HashMap1::remove(string key) {//assuming key exists in the Hashmap
	//HashNode* old = nodearray[this->findindex(key)];
	//delete old;
	nodearray[this->findindex(key)] = new HashNode("available", NULL);
	size--;
}

vector<string> HashMap1::sort_hotel() {//sorting machine
	vector<string> sort_machine;
	for (int i = 0; i < capacity; i++) {
		if (nodearray[i] != NULL && nodearray[i]->getValue() != NULL) {//ensure that we only sort where content exists
			string sort = "";//to concatenate a whole string with all information
			sort += nodearray[i]->getKey();
			for (int j = 0; j < 4; j++) {
				sort += "," + nodearray[i]->getValue()[j];
			}
			sort_machine.push_back(sort);//push the hotel name to the sorting machine
		}
	}
	sort(sort_machine.begin(), sort_machine.end());//use built-in sorting algorithm 
	return sort_machine;//return the sorted vector
}

int HashMap1::getSize() { return size; }

HashMap1::~HashMap1() {
	/*for (int i=0;i<capacity;i++){
		delete[] nodearray[i]->getValue();
	}*/
	delete[] this->nodearray;
}

HashMap2::HashMap2(int capacity) :capacity(capacity), size(0) {//constructor for hashmap2
	nodearray = new vector<HashNode*>[capacity];
}

unsigned long HashMap2::hashCode(string key)//same hashcode as hashmap1
{
	unsigned long sum = 0;
	for (int i = 0; i < key.length(); i++)
		sum += key[i] * pow(i, 10);
	return sum;
}

void HashMap2::add(string key, string* value) {//add the node under the bucket
	unsigned long index = hashCode(key) % capacity;
	for (int i = 0; i < nodearray[index].size(); i++) {
		if (nodearray[index][i]->getValue()[0] == value[0]) {//check if there is repetitive input
			cout << "The hotel existed already" << endl;
			return;
		}
	}
	nodearray[index].push_back(new HashNode(key, value));
	this->size++;
}

void HashMap2::remove(string city, string hotel) {
	unsigned long index = hashCode(city) % this->capacity;
	if (nodearray[index].empty()) { cout << "no hotel exist in such city" << endl; }
	else {
		for (int i = 0; i < nodearray[index].size(); i++) {//iterate the bucket looking for matching
			if (nodearray[index].at(i)->getValue()[0] == hotel) {
				nodearray[index].erase(nodearray[index].begin() + i);//use earse function from <vector> to delete the node
				return;
			}
		}
		cout << "cant find such hotel in the city" << endl;//no match
	}
	this->size--;
}

void HashMap2::printarray(string* v) {//printing function
	string input[5] = { "hotel name", "star", "price", "country name", "address" };
	for (int i = 0; i < 5; i++) {
		cout << input[i] << ": " << v[i] << endl;
	}
}

void HashMap2::listall(string city) {
	unsigned long index = hashCode(city) % capacity;
	if (nodearray[index].empty() || nodearray[index][0]->getKey() != city) { cout << "no hotel exist in such city" << endl; }//if no cities in the position or index matches but city wrong
	else {
		for (int i = 0; i < nodearray[index].size(); i++) {//print all citites in the bucket
			cout << "----------------" << endl;
			printarray(nodearray[index][i]->getValue());
			cout << "-------------------" << endl;
		}
	}
}

int HashMap2::getSize() { return size; }

HashMap2::~HashMap2() {
	/*for (int i=0;i<capacity;i++){
		for (int j=0; j<nodearray[i].size();j++){
			delete[] nodearray[i][j];// ->getValue();
		}
	}*/
	delete[] this->nodearray;
}

bool is_prime(int n)//check if a number is a prime
{
	if (n <= 1)  return false;//1 is not a prime
	if (n <= 3)  return true;//2,3 are primes
	if (n % 2 == 0 || n % 3 == 0) return false;
	for (int i = 5; i*i <= n; i++) {if (n%i == 0) return false;}//just check until the square root
	return true;
}