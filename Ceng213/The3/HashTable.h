#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class T>
class HashTable {
    struct Entry {
        std::string Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[3];
    };

    int _capacity; // INDICATES THE SIZE OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE



    Bucket* _table; // HASH TABLE
    // You can define private methods and variables
    int tot_prob;

public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    HashTable(const HashTable<T>& rhs);
    HashTable<T>& operator=(const HashTable<T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. 
    // IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(std::string key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
    // HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.
    void Delete(std::string key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()
    T Get(std::string key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
    void Resize(int newCapacity);
    
    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH
    double getAvgSuccessfulProbe();
    
    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH
    double getAvgUnsuccessfulProbe();

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const;
    int Size() const;
};



template <class T>
HashTable<T>::HashTable() {
// TODO: CONSTRUCTOR
    _table = NULL;
    _capacity = 0;
    tot_prob = 0;
    _size = 0;
    Resize(NextCapacity(0));

}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& rhs) {
// TODO: COPY CONSTRUCTOR
    _size = rhs._size;
    _capacity = rhs._capacity;
    tot_prob = rhs.tot_prob;

    _table = new Bucket[_capacity];

    for(int i = 0;i<_capacity;i++){
        for(int k=0;k<3;k++){
            (_table[i].entries)[k] = ((rhs._table)[i].entries)[k];
        }
    }
   
   }


template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& rhs) {
// TODO: OPERATOR=

   delete[] _table;

   
    _size = rhs._size;
    _capacity = rhs._capacity;
    tot_prob = rhs.tot_prob;

    _table = new Bucket[_capacity];

    for(int i = 0;i<_capacity;i++){
        for(int k=0;k<3;k++){
            (_table[i].entries)[k] = ((rhs._table)[i].entries)[k];
        }
    }

return *this;

}

template <class T>
HashTable<T>::~HashTable() {
// TODO: DESTRUCTOR

    delete[] _table;

}

template <class T>
void HashTable<T>::Insert(std::string key, const T& value) {
// TODO: IMPLEMENT THIS FUNCTION.
// INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
// IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
// THE ALREADY EXISTING ONE. IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
// RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.


    if((double)_size/(3*_capacity) > 0.5)
        Resize(NextCapacity(_capacity));

        int index = Hash(key)%_capacity;

        Entry newentry;
        newentry.Active = true;
        newentry.Key = key;
        newentry.Value = value;

          
        bool dolu = true;
        int m = 0;

        while(dolu){
            tot_prob++;
        for(int i = 0;i<3;i++){
            if((_table[(index+m*m)%_capacity].entries)[i].Active == false){
                (_table[(index+m*m)%_capacity].entries)[i] = newentry;
                _size++;
                dolu = false;
                break;
            }else if((_table[(index+m*m)%_capacity].entries)[i].Key == key && (_table[(index+m*m)%_capacity].entries)[i].Active == true){
                (_table[(index+m*m)%_capacity].entries)[i] = newentry;
                dolu = false;
                break;
            }else{
                dolu = true;
            }
        }
          m++;
      }

}






template <class T>
void HashTable<T>::Delete(std::string key) {
// TODO: IMPLEMENT THIS FUNCTION.
// DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
// IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
// HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.

        int index = Hash(key) % _capacity;
        int m = 0;

        while(true){
        for(int i = 0;i<3;i++){
            if((_table[(index+m*m)%_capacity].entries)[i].Active == false && (_table[(index+m*m)%_capacity].entries)[i].Deleted == false)
                return;
            else if((_table[(index+m*m)%_capacity].entries)[i].Key == key && (_table[(index+m*m)%_capacity].entries)[i].Deleted == true)
                return;
            else if((_table[(index+m*m)%_capacity].entries)[i].Key == key && (_table[(index+m*m)%_capacity].entries)[i].Active == true){
                (_table[(index+m*m)%_capacity].entries)[i].Active = false;
                (_table[(index+m*m)%_capacity].entries)[i].Deleted = true;
                _size--;
                return;
            }
            }
          m++;
      }



}

template <class T>
T HashTable<T>::Get(std::string key) const {
// TODO: IMPLEMENT THIS FUNCTION. IT SHOULD RETURN THE VALUE THAT
// IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
// IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()


        int index = Hash(key) % _capacity;
        int m = 0;

        while(true){
        for(int i = 0;i<3;i++){
            if((_table[(index+m*m)%_capacity].entries)[i].Deleted == false && (_table[(index+m*m)%_capacity].entries)[i].Active == false)
                return T();
            else if((_table[(index+m*m)%_capacity].entries)[i].Key == key && (_table[(index+m*m)%_capacity].entries)[i].Deleted == true)
                return T();
            else if((_table[(index+m*m)%_capacity].entries)[i].Key == key && (_table[(index+m*m)%_capacity].entries)[i].Active == true)
                return (_table[(index+m*m)%_capacity].entries)[i].Value;
         
      }
          m++;
      }


}

template <class T>
void HashTable<T>::Resize(int newCapacity) {
// TODO: IMPLEMENT THIS FUNCTION. AFTER THIS FUNCTION IS EXECUTED
// THE TABLE CAPACITY MUST BE EQUAL TO newCapacity AND ALL THE
// EXISTING ITEMS MUST BE REHASHED ACCORDING TO THIS NEW CAPACITY.
// WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY

    Bucket* newbucket = new Bucket[newCapacity];
    Bucket* tmp = _table;
    tot_prob = 0;

    for(int i = 0; i<_capacity; i++){
        for(int k = 0; k<3; k++){
            if((_table[i].entries)[k].Active == true){

            int index = Hash((_table[i].entries)[k].Key) % newCapacity;
            Entry item = (_table[i].entries)[k];

        int m = 0;
        bool dolu = true;

        while(dolu){
            tot_prob++;
        for(int s = 0;s<3;s++){
            if((newbucket[(index+m*m)% newCapacity].entries)[s].Active == false){
               (newbucket[(index+m*m)% newCapacity].entries)[s] = item;
               dolu = false;
               break;
            }else if((newbucket[(index+m*m)% newCapacity].entries)[s].Key == item.Key && (newbucket[(index+m*m)% newCapacity].entries)[s].Active == true){
               (newbucket[(index+m*m)% newCapacity].entries)[s] = item;
               dolu = false;
               break;
            }else
               dolu = true;
        }
          m++;
      }
        }
    }
}
    
    _capacity = newCapacity;
    _table = newbucket;

    delete[] tmp;

}


template <class T>
double HashTable<T>::getAvgSuccessfulProbe() {
// TODO: IMPLEMENT THIS FUNCTION.
// RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH

    if(_size == 0)
        return 1;

return (double)tot_prob/_size;

}

template <class T>
double HashTable<T>::getAvgUnsuccessfulProbe() {
// TODO: IMPLEMENT THIS FUNCTION.
// RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH


    int tot_num = 0;


    for(int i = 0; i<_capacity; i++){

        int index = i;
        int m = 0;
        bool notfound = true;

        while(notfound){
            tot_num++;
        for(int k = 0;k<3;k++){
            if((_table[(index + m*m) % _capacity].entries)[k].Deleted == false && (_table[(index + m*m) % _capacity].entries)[k].Active == false){
               notfound = false;
               break;
            }
         }
          m++;
      }
            }

     return (double)tot_num/(_capacity);

    }
    
    

template <class T>
int HashTable<T>::Capacity() const {
    return _capacity;
}

template <class T>
int HashTable<T>::Size() const {
    return _size;
}

#endif