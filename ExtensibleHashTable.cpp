#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#include "HashTable.cpp" //must be in same local folder

class ExtensibleHashTable: public HashTable {
private:
    double upper_bound_ratio, lower_bound_ratio;

    void rehash();
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

ExtensibleHashTable::ExtensibleHashTable(double upp_bound_ratio,double lower_bound_ratio,int size) :HashTable(size),upper_bound_ratio(upp_bound_ratio),lower_bound_ratio(lower_bound_ratio){}
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
    double boundRatio = double(size) / double(capacity);
    //Hold all the elements of the old HashTable
    int oldCapacity=capacity;
    string *oldTable;
    oldTable = new string[oldCapacity];
    for (int i = 0;i <oldCapacity;i++){
        oldTable[i] = table[i];
    }
    
    if ( boundRatio > upper_bound_ratio){//2x table, inserts elements again
        int newCapacity = 2 * capacity;
        capacity=newCapacity;
        size=0;
        delete [] table; //delete memory allocated by our *current* table pointer
        table = new string[capacity]; //new memory allocation for our *current* table pointer
        
         for (int i = 0 ; i < oldCapacity ; i++) {
            if( !(oldTable[i].empty()) && (oldTable[i].compare("##tomb##"))!=0 ) {
                //replace with isAvailable(?)
                HashTable::add(oldTable[i]);
            }
         }
    }
    else if(boundRatio < lower_bound_ratio){
        int newCapacity = capacity/2;
        capacity=newCapacity;
        size=0;
        delete [] table; //delete memory allocated by our *current* table pointer
        table = new string[capacity]; //new memory allocation for our *current* table pointer
        
        for (int i = 0 ; i < oldCapacity ; i++) {
            if( !(oldTable[i].empty()) && (oldTable[i].compare("##tomb##"))!=0 ) {//replace with isAvailable(?)
                HashTable::add(oldTable[i]);
            }
         }
    }
    else{
        size= -2;
    }
}

//"add" adds a string into the HashTable
bool ExtensibleHashTable::add(const string &str){
    //check what should happen before putting the the string
    int olds=this->size;
    this->size=this->size+1;
    ExtensibleHashTable::rehash();
    if(this->size==-2){
        this->size=olds;
    }
    HashTable::add(str);
}
//"remove" removes a string from  the HashTable
bool ExtensibleHashTable::remove(const string &str){
    int olds=this->size;
    this->size=this->size-1;
    ExtensibleHashTable::rehash();
    
     if(this->size==-2){
        this->size=olds;
    }
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

  ExtensibleHashTable newExtensiveHashTable;
  for (int i=0;i<this->capacity;i=i+1){
    if(!(this->table[i].empty()) && (this->table[i].compare("##tomb##"))!=0){ //if there is a key in this pos
      newExtensiveHashTable.add(this->table[i]); //insert it in the new one
    }
  }
  for (int i=0;i<t.capacity;i=i+1){
    if(!(t.table[i].empty()) && (t.table[i].compare("##tomb##"))!=0){ //if there is a key in this pos
      newExtensiveHashTable.add(t.table[i]); //insert it in the new one
    }
  }
   
  return newExtensiveHashTable;
}


ExtensibleHashTable &ExtensibleHashTable::operator+=(const ExtensibleHashTable &t){
//uses others operators (= , +)
    *this = *this+t;
}

ExtensibleHashTable &ExtensibleHashTable::operator=(const ExtensibleHashTable &t){
    //checks for the new size of the table array

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
    
    return *this;
}
