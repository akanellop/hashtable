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
	bool isEmpty(int pos);//done & works
	bool isTomb(int pos);//done & works
	bool isAvailable(int pos);//done & works
	bool contains(const string &s);//done & works
	bool contains(const char *s);//done & works
	virtual bool add(const string &s); 	//done & works
	virtual bool add(const char *s);		//done & works
	virtual bool remove(const string &s); //done & works
	virtual bool remove(const char *s); //done & works
	void print(); // done & works

	virtual bool operator << (string str); //done & works
	virtual bool operator >> (string str); //done & works
	HashTable operator+(HashTable &t);//done & works
	HashTable &operator+=(HashTable &t);//done & works
	HashTable &operator=(const HashTable &t);//done & works

	~HashTable(); // done & works

private: //not needed (?)
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
}
//Copy Constructor ##TO-DO : reminder to ask for size!
HashTable::HashTable(const HashTable &ht){
	this->capacity = ht.capacity;	//xwrhtikothta
	this->size = ht.size;					//#apothikeumena stoixeia
	this->table = new string[ht.capacity];

	for (int i =0 ; i < capacity ; i++){
		this->table[i].assign(ht.table[i]);
	}
}

//Destructor
HashTable::~HashTable(){
	delete [] table;
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
If it's already there, it returns false, otherwise..true.
Help Function:"contains"
*/
bool HashTable::add(const string &s){
	int startPosition;
	//checks if word is in table
	bool existsAlready = HashTable::contains(s);

	//will procceed to insertion if the string doesn't already exist in table
	if ( existsAlready == false ) {
		int hashCode =  HashTable::getHashCode(s);

		startPosition = hashCode % capacity; //our modulo math type

		//if startPosition is available, then assign
		if(isAvailable(startPosition)== true){
			table[startPosition].assign(s);
			size++;
			//print();
			return true;
		}else{ //if startPosition not available, then do linear probing
			int currentPosition = startPosition;

			do{
				currentPosition = (currentPosition + 1) % capacity;
				if(isAvailable(currentPosition) == true){ //if avail, assign
					table[currentPosition].assign(s);
					size++;
					//  print();
					return true;
				}
			}while(currentPosition!=startPosition); //till we reach where we started
		}
	}
	//if the word is already there or the array is full , return false
	return false;
}
//pointer to char version
bool HashTable::add(const char *s){
	string str(s);
	return HashTable::add(str);
}

/*
"remove" deletes a string from the hashtable
*/
bool HashTable::remove(const string &s){
	int startPosition;
	//checks if word is in table
	bool existsAlready = HashTable::contains(s);
	//will procceed to deletion if the string exists in table
	if (existsAlready == true ) {
		int hashCode =  HashTable::getHashCode(s);
		startPosition = hashCode % capacity;

		//If the string is in the startPosition, remove it.
		if (table[startPosition].compare(s) == 0) {
			table[startPosition].assign("##tomb##");
			size--;
			return true;
		}
		else	{//else continue searching the table for its position
			int currentPosition=startPosition;
			do{
				currentPosition = (currentPosition + 1) % capacity; //next position
				if(table[currentPosition].compare(s) == 0){ //string compare
					table[currentPosition].assign("##tomb##");
					size--;
					return true;
				}
			}while(currentPosition!=startPosition); //till we start the end
		}
	}

	//if the word didnt exist in table , return false
	return false;
}
//pointer to char version
bool HashTable::remove(const char *s){
	string str(s);
	return HashTable::remove(str);
}

/*
"contains" searches the hashtable to find the given string.
If it's there, it returns the index.
Otherwise, it returns -1(error)
Help Function: "isNull"
*/
bool HashTable::contains(const char *str){
	int hashCode = HashTable::getHashCode(str); //get hashcode
	int startPosition = hashCode % capacity;
	int i = startPosition; //get position to start from

	do {
		//checks if there is an item with same hashcode in table[index],
		// if there is not, we're free to write
		if ( HashTable::isAvailable(i) ){
			return false;
		}
		//if there is an item, we check if it is our  string
		if (table[i].compare(str) == 0) {
			return true;
		}
		//if the position is occupied but not from the current sting we keep searching
		else {
			i = (i + 1) % capacity;
		}
	} while (i != startPosition); //till we reach our startPosition

	return false;
}
//pointer to char version
bool HashTable::contains(const string &s) {
	const char *str = s.c_str();
	return HashTable::contains(str);
}

//isEmpty searches table[i] and returns true if the item there is empty, otherwise false
bool HashTable::isEmpty(int pos){
	if ( table[pos].empty() ){
		return true;
	}
	else {
		return false;
	}
}

//isTomb checks if table[i] is a deleted item(tomb)
bool HashTable::isTomb(int pos){
	if (table[pos].compare("##tomb##") == 0) {
		return true;
	}
	else{
		return false;
	}
}

//isAvailable checks if table[i] can be written with an item-string
bool HashTable::isAvailable(int pos){
	if ( (isEmpty(pos)==true ) || (isTomb(pos)==true) ) {
		return true;
	}
	else{
		return false;
	}
}

//"print" prints the HashTable
void HashTable::print(){
	for( int i = 0 ; i < capacity; i++){

        if(!(isAvailable(i)) || (isTomb(i)) ){
		    cout << "position " << i << " -> " << table[i] << endl;
        }
	}
	cout << "capacity : " << capacity << " size : " << size  << endl;
}

//"add" operator
bool HashTable::operator<<(string s){
	string str(s); //overkill
	return HashTable::add(str);
}

//"remove" operator
bool HashTable::operator>>(string s){
	string str(s); //overkill
	return HashTable::remove(str);
}

//"+" operator for 2 HashTable objects
HashTable HashTable::operator+(HashTable &t){
	//create new object and initialize it with both tables
	int newCapacity = this->capacity + t.capacity;
	HashTable newHashTable(newCapacity);
	//eg: table3 = table1 + table2
	//The following code adds all items of table1 to table3
	//same thing to table 2
	for (int i=0;i<this->capacity;i=i+1){
		if(!(this->isAvailable(i))){ //if there is a key in this pos
			newHashTable.add(this->table[i]); //insert it in the new one
		}
	}

	for (int i=0;i<t.capacity;i=i+1){ //WHY IS THIS COMMENTED?
		if(!(t.isAvailable(i))){		//if there is a key in this pos
			newHashTable.add(t.table[i]);	//insert it in the new one
		}
	}
	return newHashTable;
}

//"+=" operator for 2 HashTable objects
HashTable &HashTable::operator+=(HashTable &t){
	//uses others operators (= , +)
	*this = *this+t;
}

//"=" operator for 2 HashTable objects.It copies a hashtable into an existing one"
HashTable &HashTable::operator=(const HashTable &t){
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
    return *this;
}

//int main(){}
