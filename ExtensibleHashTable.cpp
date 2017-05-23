#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#include "HashTable.cpp"

class ExtensibleHashTable: public HashTable {
private:
  double upper_bound_ratio, lower_bound_ratio;
  void rehash();
  void rehash(int newcapacity);

public:
  //Constructors
  ExtensibleHashTable(double upper_bound_ratio=0.5,
                      double lower_bound_ratio=0.125,
                      int size=8);
  ExtensibleHashTable(const ExtensibleHashTable &t);

  //Just like parents-calls inside rehash()
  bool add(const string &str);
  bool remove(const string &str);
  //Just like parents- might not be needed to be implemented
  bool operator << (string str);
  bool operator >> (string str);

  //operators -- Why aren't they the same like parents?!
  ExtensibleHashTable operator+(const ExtensibleHashTable &t) const;
  ExtensibleHashTable &operator+=(const ExtensibleHashTable &t);
  ExtensibleHashTable &operator=(const ExtensibleHashTable &t);
};

//Constructor
ExtensibleHashTable::ExtensibleHashTable(double upper_bound_ratio,
                    double lower_bound_ratio,
                    int size){

                      this->upper_bound_ratio = upper_bound_ratio;
                      this->lower_bound_ratio = lower_bound_ratio;
                      this->capacity = size;
                      this->size = 0;

                      this->table = new string[this->capacity];
                      cout << "New ExtensibleHashTable got created! " << endl <<endl;
                    }

//Copy Constructor
ExtensibleHashTable::ExtensibleHashTable(const ExtensibleHashTable &t) {

  this->upper_bound_ratio = t.upper_bound_ratio;
  this->lower_bound_ratio = t.lower_bound_ratio;
  this->capacity = t.capacity;
  this->size = t.size;

  this->table = new string[this->capacity];
  for (int i = 0;i <this->capacity;i++){
    this->table[i] = t.table[i];
  }
}




void ExtensibleHashTable::rehash() {

                    }
