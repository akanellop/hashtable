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
    ExtensibleHashTable(double upper_bound_ratio=0.5,double lower_bound_ratio=0.125,int size=8); //done
    ExtensibleHashTable(const ExtensibleHashTable &t); //done

  //Just like parents-calls inside rehash()
    bool add(const string &str);
    bool remove(const string &str);
    bool operator << (string str);
    bool operator >> (string str);

    ExtensibleHashTable operator+(const ExtensibleHashTable &t) const;
    ExtensibleHashTable &operator+=(const ExtensibleHashTable &t);
    ExtensibleHashTable &operator=(const ExtensibleHashTable &t);
};

//Constructor

ExtensibleHashTable::ExtensibleHashTable(double upp_bound_ratio,double lower_bound_ratio,int size) :HashTable(size),upper_bound_ratio(upp_bound_ratio),lower_bound_ratio(lower_bound_ratio){
    cout << "New ExtensibleHashTable got created! " <<endl;
}


/* //Second Way - Classic Constructor
ExtensibleHashTable::ExtensibleHashTable(double upper_bound_ratio,double lower_bound_ratio,int size) {
    //HashTable(size);
    this->capacity = size; //xwrhtikothta
    this->size = 0;        //#apothikeumena stoixeia

    this->table = new string[this->capacity]; //static memory alloc //(nothrow?)
    this->upper_bound_ratio = upper_bound_ratio;
    this->lower_bound_ratio = lower_bound_ratio;
}
*/


//Copy Constructor
ExtensibleHashTable::ExtensibleHashTable(const ExtensibleHashTable &t) {
    upper_bound_ratio = t.upper_bound_ratio;
    lower_bound_ratio = t.lower_bound_ratio;
    size=t.size;
    capacity=t.capacity;
    table = new string[capacity];
    for (int i = 0;i <capacity;i++){
        table[i] = t.HashTable::table[i];
    }
}

//rehashing method
void ExtensibleHashTable::rehash(){

    double boundRatio = size / capacity;

    //Hold all the elements of the old HashTable
    int oldCapacity=capacity;
    string *oldTable;
    oldTable = new string[oldCapacity];
    for (int i = 0;i <oldCapacity;i++){
        oldTable[i] = table[i];
    }

    if ( boundRatio > upper_bound_ratio){
        //2x table, inserts elements again

        //"construct" new one
        int newCapacity = 2 * capacity;
        capacity=newCapacity;
        size=0;
        delete [] table; //delete memory allocated by our *current* table pointer
        table = new string[capacity]; //new memory allocation for our *current* table pointer

        //start filling new hashtable
        string word;
        int startPosition;
        //This code is similar to HashTable::add . Go check that one.
        //for each word in our *old* table, assign it to our new bigger one
        for (int i = 0 ; i < oldCapacity ; i++) {
            word = oldTable[i];
            if( !word.empty() && !word.compare("") && !word.compare("##tomb##") ) { //replace with isAvailable (?)
                HashTable::add(word);
            }
        }
    }
    else{
        int newCapacity = capacity/2;
        capacity=newCapacity;
        size=0;
        delete [] table; //delete memory allocated by our *current* table pointer
        table = new string[capacity]; //new memory allocation for our *current* table pointer

        //start filling our new hashtable
        string word;
        //for each word in our *old* table, assign it to our new bigger one
        for (int i = 0 ; i < oldCapacity ; i++) {
            word = oldTable[i];
            if( !word.empty() && !word.compare("") && !word.compare("##tomb##") ) {//replace with isAvailable(?)
                HashTable::add(word);
            }
        }
    }
}

void ExtensibleHashTable::rehash(int newcapacity){
}

//nomizeis mono ayto prepei na kanoyme ?
//rehash kai add sketo?

//Nai.
//-Lefteris.

//"add" adds a string into the HashTable
bool ExtensibleHashTable::add(const string &str){
    //check what should happen before putting the the string
    cout << getSize() <<endl;
    size++;
    cout << getSize() <<endl;
    //this->size = size+1;
    ExtensibleHashTable::rehash();
    size--;//function "add" will increment the size finally.
    HashTable::add(str);
}

//"remove" removes a string from  the HashTable
bool ExtensibleHashTable::remove(const string &str){
    //this->size = size + 1;
    size--;
    ExtensibleHashTable::rehash();
    size++;//function "remove" will decrease the size finally.
    HashTable::remove(str);
}

//"add" operator for 1 ExtensibleHashTable object
bool ExtensibleHashTable::operator<<(string str){
	return ExtensibleHashTable::add(str);
}

//"remove" operator for 1 ExtensibleHashTable object
bool ExtensibleHashTable::operator>>(string str){
    return ExtensibleHashTable::remove(str);
}

ExtensibleHashTable ExtensibleHashTable::operator+(const ExtensibleHashTable &t) const{
//rehash here or bottom? Or maybe it's no needed because add will do it anyways
    double sth1;
    double sth2;

  int newCapacity = this->capacity + t.capacity;
  ExtensibleHashTable newExtensiveHashTable( sth1,sth2, newCapacity);//hope this gets compiled
  for (int i=0;i<this->capacity;i=i+1){
    if(!(newExtensiveHashTable.isAvailable(i))){ //if there is a key in this pos
      newExtensiveHashTable.add(this->table[i]); //insert it in the new one
    }
  }
  for (int i=0;i<t.capacity;i=i+1){
    //if(!(t.isAvailable(i))){		//if there is a key in this pos
      newExtensiveHashTable.add(t.table[i]);	//insert it in the new one
    //}
  }
//rehash here or top?? Or maybe it's no needed because add will do it anyways
  return newExtensiveHashTable;
}


ExtensibleHashTable &ExtensibleHashTable::operator+=(const ExtensibleHashTable &t){
//uses others operators (= , +)
    *this = *this+t;
}

ExtensibleHashTable &ExtensibleHashTable::operator=(const ExtensibleHashTable &t){
    //checks for the new size of the table array

    //rehash?
	if(this->capacity!=t.capacity){
		delete [] this->table;
		this->table = new string[t.capacity];
	}

	this->size=t.size;
	this->capacity=t.capacity;
	//copies strings
	for(int i=0;i<capacity;i=i+1){
		this->table[i]=t.table[i];
	}
    this->upper_bound_ratio = t.upper_bound_ratio;
    this->lower_bound_ratio = t.lower_bound_ratio;
    //rehash?
}


int main(){
    ExtensibleHashTable e1(10,10,10);
    e1.add("katerina");
    ExtensibleHashTable e2(10,10,14);
    //how to call contructor with pre-defined values for first parameters?
    //e2.add("nig");
    ExtensibleHashTable e3;
    e2.print();
//    e2+=e1;
    //e2+=e1;
}
