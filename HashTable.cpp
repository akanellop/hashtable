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
  virtual bool add(const string &s);
  virtual bool add(const char *s);
  virtual bool remove(const string &s);
  virtual bool remove(const char *s);
  void print();

  virtual bool operator << (string str);
  virtual bool operator >> (string str);
  HashTable operator+(HashTable &t);
  HashTable &operator+=(HashTable &t);
  HashTable &operator=(const HashTable &t);

};
