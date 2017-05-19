#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class HashTable {
protected:
	unsigned int size;
	unsigned int capacity;
	string *table;
	static int getHashCode(const char *str); //done

public:
	HashTable(int size=8); // done
	HashTable(const HashTable &ht);
	int getSize();
	int getCapacity(); // done
	bool isEmpty(int pos);
	bool isTomb(int pos);
	bool isAvailable(int pos);
	bool contains(const string &s);
	bool contains(const char *s);
	virtual bool add(const string &s); 	//done
	virtual bool add(const char *s);		//done

	/*virtual bool remove(const string &s);
	virtual bool remove(const char *s);*/
	void print();

	/*virtual bool operator << (string str);
	virtual bool operator >> (string str);*/
	HashTable operator+(HashTable &t);
	HashTable &operator+=(HashTable &t);
	HashTable &operator=(const HashTable &t);

	~HashTable();

private:
	int searchTableFor(const char *str);
	int searchTableFor(const string &s);
	bool isNull(int i);
	int getHashCode(const string &s);


};

/*
'getHashCode' returns the ASCII sum of a word given by iterating through each character in string 'str' and typecasting each it to an integer.
*/
int HashTable::getHashCode(const char *str) {
	int sum = 0;
	int len = strlen(str);

	for (int i=0; i <len; i++) {
		sum += (int)str[i];
	}

	return sum;
}
int HashTable::getHashCode(const string &s) {
	const char *str = s.c_str();
	return HashTable::getHashCode(str);
}

//Constructor for the class with size as input(default size = 8)
HashTable::HashTable(int size) {
	this->capacity = size; //xwrhtikothta
	this->size = size;        //#apothikeumena stoixeia

	table = new string[size]; //static memory alloc //(nothrow?)
	cout << "HashTable got created!" << endl;
}


//Copy Constructor ##TO-DO : reminder to ask for size!
HashTable::HashTable(const HashTable &ht){
	this->capacity = ht.capacity;	//xwrhtikothta
	this->size = ht.size;					//#apothikeumena stoixeia
	this->table = new string[ht.size];

	for (int i =0 ; i < size-1 ; i++){
		this->table[i].assign(ht.table[i]);
	}
	cout << "HashTable got created with Copy-Constructor!" << endl;
}


//Destructor
HashTable::~HashTable(){
	delete [] table;
	cout << "HashTable got deleted!" << endl;
}

//getCapacity returns capacity
int HashTable::getCapacity(){
	return capacity;
}

/*
"add" adds a string into the table.
If it's there, it returns false, otherwise..true.
Help Function:"searchTableFor"
*/
bool HashTable::add(const string &s){
	//search if already there
	int index = HashTable::searchTableFor(s);
	if (index == -1 ) {//if not, insert and return true
		int hashCode =  HashTable::getHashCode(s);
		index = hashCode % size;
		table[index].assign(s);
		return true;
	}

	//if already there, return false
	return false;

}

bool HashTable::add(const char *s){
	string str(s);
	return HashTable::add(str);

}
/*
searchTableFor searches the hashtable to find the given string.
If it's there, it returns the index.
Otherwise, it returns -1(error)
Help Function: "isNull"
*/
int HashTable::searchTableFor(const char *str){
	int hashCode = HashTable::getHashCode(str);
	int startPosition = hashCode % size;
	int i = startPosition;

	do {
		if ( HashTable::isNull(i) ){
			return -1;
		}
		if (table[i].compare(str) == 0) {
			return i;
		}
		else {
			i = (i + 1) % size;
		}
	} while (i != startPosition);

	return -1;
}

int HashTable::searchTableFor(const string &s) {
	const char *str = s.c_str();
	return HashTable::searchTableFor(str);
}

//isNull searches table[i] and returns true if the item there is null
bool HashTable::isNull(int i){
	if ( table[i].empty() ){
		return true;
	}
	else {
		return false;
	}
}


int main(){
	//int test1 = HashTable::getHashCode("apple");
	//cout << test1 <<endl ;
	cout << "hello, all good till now " <<endl;


}
