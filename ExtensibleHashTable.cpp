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
    ExtensibleHashTable(double upp_bound_rat=0.5,double low_bound_rat=0.125,int size=8); //done
    ExtensibleHashTable(const ExtensibleHashTable &t); //done

  //Just like parents-calls inside rehash()
    bool add(const string &str);
   /* bool remove(const string &str);
    bool operator << (string str);
    bool operator >> (string str);

    ExtensibleHashTable operator+(const ExtensibleHashTable &t) const;
    ExtensibleHashTable &operator+=(const ExtensibleHashTable &t);
    ExtensibleHashTable &operator=(const ExtensibleHashTable &t);
*/};

//Constructor
ExtensibleHashTable::ExtensibleHashTable(double upp_bound_rat,double low_bound_rat,int size) :HashTable(size),upper_bound_ratio(upp_bound_rat),lower_bound_ratio(low_bound_rat){
    cout << "New ExtensibleHashTable got created! " <<endl;
}

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
    //holding on the old elements
    //
    //// ena ena kai oxi antikeimeno gt den evlepe ta protected pedia toy mias kai itan diaforetiko antikeimeno
    int oldc=capacity;
    string *oldt;
    oldt = new string[oldc];
    for (int i = 0;i <oldc;i++){
        oldt[i] = table[i];
    }
    
    if( boundRatio > upper_bound_ratio){
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
        for (int i = 0 ; i < oldc ; i++) {
            word = oldt[i];
            if( !word.empty() && !word.compare("") && !word.compare("##tomb##") ){
                HashTable::add(word);
            }
        }
    }
    else{
        int newCapacity =capacity/2;
        capacity=newCapacity;
        size=0;
        delete [] table; //delete memory allocated by our *current* table pointer
        table = new string[capacity]; //new memory allocation for our *current* table pointer
        
        //start filling new hashtable
        string word;
                //for each word in our *old* table, assign it to our new bigger one
        for (int i = 0 ; i < oldc ; i++) {
            word = oldt[i];
            if( !word.empty() && !word.compare("") && !word.compare("##tomb##") ){
                HashTable::add(word);
            }
        }
    }
}

void ExtensibleHashTable::rehash(int newcapacity){
}

//nomizeis mono ayto prepei na kanoyme ?
//rehash kai add sketo?
//episis checkare ayto poy exo sto comment me to size 
//prepei na do an tha ginei rehash me to neo stoixeio hh prpei na kano rehash prin apodekto to neo stoixeio?
bool ExtensibleHashTable::add(const string &str){
    //check what should happen before putting the the string
    //size=size+1;
    rehash();
    //size=size-1;
    HashTable::add(str);
} // tha ginoun kai oles oi ipoloipes etsi ?

int main(){
    ExtensibleHashTable e1(10);
    e1.add("katerina");
    ExtensibleHashTable e2(e1);
    e2.print();
}