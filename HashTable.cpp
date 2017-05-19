#include <cstring>
#include <iostream>

using namespace std;

class HashTable {
protected:
    unsigned int size;
    unsigned int capacity;
    string *table;
    static int getHashCode(const char *str);

public:
    HashTable(int size=8);
    HashTable(const HashTable &ht);
    int getSize();
    int getCapacity();
    bool isEmpty(int pos);
    bool isTomb(int pos);
    bool isAvailable(int pos);
    bool contains(const string &s);
    bool contains(const char *s);
    /*virtual bool add(const string &s);
    virtual bool add(const char *s);
    virtual bool remove(const string &s);
    virtual bool remove(const char *s);*/
    void print();

    /*virtual bool operator << (string str);
    virtual bool operator >> (string str);*/
    HashTable operator+(HashTable &t);
    HashTable &operator+=(HashTable &t);
    HashTable &operator=(const HashTable &t);

		~HashTable();

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

//Constructor for the class with size as input(default size = 8)
  HashTable::HashTable(int size) {
    this->capacity = size; //xwrhtikothta
    this->size = 0;        //#apothikeumena stoixeia

    table = new string[size]; //static memory alloc

		cout << "HashTable got created!" << endl;
  }


//Destructor
	HashTable::~HashTable(){
		delete [] table;
		cout << "HashTable got deleted!" << endl;
	}


  int main(){
    //int test1 = HashTable::getHashCode("apple");
    //cout << test1 <<endl ;


  }
