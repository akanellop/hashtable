#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class HashTable {
protected:
	unsigned int size;
	unsigned int capacity;
	string *table;
	static int getHashCode(const char *str); //done & works

public:
	HashTable(int size=8); // done & works
	HashTable(const HashTable &ht); //done
	int getSize(); //done & works
	int getCapacity(); // done & works
	bool isEmpty(int pos);//done
	bool isTomb(int pos);//done
	bool isAvailable(int pos);//done
	bool contains(const string &s);
	bool contains(const char *s);
	virtual bool add(const string &s); 	//done & works
	virtual bool add(const char *s);		//done & works

	/*virtual bool remove(const string &s);
	virtual bool remove(const char *s);*/
	void print(); // done & works

	/*virtual bool operator << (string str);
	virtual bool operator >> (string str);*/
	HashTable operator+(HashTable &t);
	HashTable &operator+=(HashTable &t);
	HashTable &operator=(const HashTable &t);

	~HashTable(); // done & works

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
int HashTable::getHashCode(const string &s) { //string version
	const char *str = s.c_str();
	return HashTable::getHashCode(str);
}

//Constructor for the class with size as input(default size = 8)
HashTable::HashTable(int size) {
	this->capacity = size; //xwrhtikothta
	this->size = 0;        //#apothikeumena stoixeia

	table = new string[this->capacity]; //static memory alloc //(nothrow?)
	cout << "HashTable got created!" << endl << endl;
}

//Copy Constructor ##TO-DO : reminder to ask for size!
HashTable::HashTable(const HashTable &ht){
	this->capacity = ht.capacity;	//xwrhtikothta
	this->size = ht.size;					//#apothikeumena stoixeia
	this->table = new string[ht.capacity];

	for (int i =0 ; i < capacity ; i++){
		this->table[i].assign(ht.table[i]);
	}
	cout << "HashTable got created with Copy-Constructor!" << endl << endl ;
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

//getSize returns size
int HashTable::getSize(){
	return size;
}

/*
"add" adds a string into the table.
If it's there, it returns false, otherwise..true.
Help Function:"searchTableFor"
*/
bool HashTable::add(const string &s){ 
    cout<<endl;
	cout << endl << "Word is = " << s <<endl;
    //checks if word is in table
	int index = HashTable::searchTableFor(s);
	
    //will procceed to insertion if the string does not already exists in table
    if (index == -1 ) {
		int hashCode =  HashTable::getHashCode(s);
        //index:where to start searching in table, based on hashcode
		index = hashCode % capacity;
		//cout<< "index is :  " << index <<endl;
		
        //if the pos-index is available proceed
        if(isAvailable(index)== true){
            table[index].assign(s);
            size++;
            print();
            return true;
        }
        //else continue searching the table for available positions
        else{
            int iter=index;
            do{
                iter = (iter + 1) % capacity;
                if(isAvailable(iter) == true){
                    table[iter].assign(s);
                    size++;
                    print();
		            return true;
                }
            }while(iter!=index);  
        }
	}
    
    //if the word is already there or the array is full , return false
	cout <<s <<" :already there or table already full" <<endl;
    cout<<endl;
	//print();
	return false;

}
//pointer to char version
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
	int startPosition = hashCode % capacity;
	int i = startPosition;
    
	do { 
        //checks is there is an item with same hascode in table[index],
        // if there is not were free to write
		if ( HashTable::isAvailable(i) ){
			return -1;
		}
        //if there is one we check if it is our current string
		if (table[i].compare(str) == 0) { 
			return i;
		}
        //if the position is occupied but not from the current sting we keep searching
		else {
			i = (i + 1) % capacity;
		}
	} while (i != startPosition);

	return -1;
}
//pointer to char version
int HashTable::searchTableFor(const string &s) { 
	const char *str = s.c_str();
	return HashTable::searchTableFor(str);
}
//isEmpty searches table[i] and returns true if the item there is null
bool HashTable::isEmpty(int i){
	if ( table[i].empty() ){
		return true;
	}
	else {
		return false;
	}
}
//isTomb checks if table[i] is a removed item
bool HashTable::isTomb(int pos){
    if (table[pos].compare("##tomb##") == 0) { //checkarw string
			return true;
	}
    else{
        return false;
    }
};
//isAvailable checks if table[i] can be written
bool HashTable::isAvailable(int pos){
    if ((isEmpty(pos)==true )||(isTomb(pos)==true)) { //checkarw string
			return true;
	}
    else{
        return false;
    }
};
//"print" prints the HashTable
void HashTable::print(){
	for( int i = 0 ; i < capacity; i++){
		cout << "position " << i << " -> " << table[i] << endl;
	}
	cout << "capacity : " << capacity << " size : " << size  << endl;

}


int main(){
    //creates HashTable of given size
    HashTable table(6);
    //inserts few elements
    table.add("apple");
    table.add("lollipop");
    table.add("ppale");
    //uncomment to print final HashTable
    //table.print();
    
    
    
    
	//int test1 = HashTable::getHashCode("apple");
	//cout << test1 <<endl ;
	//cout << "hello, all good till now " <<endl;
	table.add("applewew");
    table.add("applesdfs");
	table.add("lollipop");
	table.add("ppale");
    table.add("appel");
   // table.add("paple");
    //table.add("lpape");
	table.add("ehehehe");


}
