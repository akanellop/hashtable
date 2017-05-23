#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#include "HashTable.cpp" //must be in same local folder

class ExtensibleHashTable: public HashTable {
private:
  double upper_bound_ratio, lower_bound_ratio;
  void rehash();
  void rehash(int newcapacity);

public:
  //Constructors
  ExtensibleHashTable(double upper_bound_ratio=0.5,
                      double lower_bound_ratio=0.125,
                      int size=8); //done
  ExtensibleHashTable(const ExtensibleHashTable &t); //done

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

//"rehash" checks if the table should be rehashed and rehashes it.
void ExtensibleHashTable::rehash() {
  double boundRatio = size / capacity;

  //for adds
  if ( boundRatio > upper_bound_ratio){
    //2x table, inserts elements again
    unsigned int oldCapacity = capacity;
    unsigned int newCapacity = 2 * capacity;

    HashTable oldHashTable(*this); //copy construct, from there we will get the strings
    delete [] table; //delete memory allocated by our *current* table pointer

    //"construct" new one
    this->capacity = newCapacity;
    this->size = 0;
    this->table = new string[capacity]; //new memory allocation for our *current* table pointer

    string word;
    int hashCode;
    int startPosition;

    //This code is similar to HashTable::add . Go check that one.
    //for each word in our *old* table, assign it to our new bigger one
    for (int i = 0 ; i < oldCapacity ; i++) {
      word = oldHashTable.table[i];
      //cout << endl << "Word to add  = " << word <<endl;

		  hashCode =  HashTable::getHashCode(word);
      startPosition = hashCode % this->capacity;

  		//if startPosition is available, then assign
  		if(HashTable::isAvailable(startPosition)== true){
  			this->table[startPosition].assign(word);
  			this->size++;

  			//return true;
        //continue;
  		}else{ //ifstartPosition not available, then do linear probing
  			int currentPosition = startPosition;

  			do{
  				currentPosition = (currentPosition + 1) % capacity;
  				if(HashTable::isAvailable(currentPosition) == true){ //if avail, assign
  					this->table[currentPosition].assign(word);
  					this->size++;
  					//return true;
            //continue;
  				}
  			}while(currentPosition!=startPosition); //till we reach where we started
		  }
    }

  //for removes
  if ( boundRatio < lower_bound_ratio){
    // x/2 table, inserts elements again
  }

}
