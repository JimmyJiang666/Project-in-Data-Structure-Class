#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<string>
#include<vector>
#include<iterator>

using namespace std;

class HashNode
{
public:
	HashNode(string key, string* value);
	string getKey();
	string* getValue();
	~HashNode();
private:
	string key;
	string* value;//an array storing all values of a hotel

};

class HashMap1
{
public:
	HashMap1(int capacity);
	unsigned long hashCode(string key);
	void add(string key, string* value);
	string* find(string key, int& comparison);
	int findindex(string key);
	void remove(string key);
	vector<string> sort_hotel();
	int getSize();
	~HashMap1();
private:
	HashNode** nodearray;//an array storing all hotels as hashnodes
	int size;
	int capacity;
};

class HashMap2
{
public:
	HashMap2(int capacity);
	unsigned long hashCode(string key);
	void add(string key, string* value);
	void remove(string city, string hotel);
	void printarray(string* v);
	void listall(string city);
	int getSize();
	~HashMap2();

private:
	vector<HashNode*>* nodearray;//array storing vectors containing all hotels in a city as hashnodes
	int size;
	int capacity;
};

bool is_prime(int n);//boolean function to determine a prime
