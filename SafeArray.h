#pragma once
#include <iostream>
#include <stdlib.h>
#include "SafeArrayExceptions.h"

using namespace std;

template <class T>
class SafeArray
{
 public:
  SafeArray();
  SafeArray(int initSize);
  SafeArray(SafeArray <T> & otherArray);
  ~SafeArray();
  T& at(int i) const;
  int getCapacity();
  int size() const;
  void push_back(const T& element);
  void push_back(const SafeArray <T>& newArray);
  T pop_back();
  void resize(int newSize);
  void print();
  T& operator[](int pos) const;
  void insert(int position, const T&);
  void insert(int position, const SafeArray <T>& elements);
  T remove(int position);
  bool removeElement(T element);
  void removeRange(int startIndex, int endIndex);
  
 private:
  T* p_array;
  int capacity;
  int currentSize;
};

//constructor implementation
template <class T>
SafeArray <T> :: SafeArray()
{
  //cout << "SafeArray default constructor called" << endl;

  //initialize size of array
  capacity = 10;
  cout << "Array has been initialized with capacity of 10" << endl;
  
  //create new array of things on the heap
  p_array = new T[capacity];

  //initialize array position
  currentSize = 0;
  
}

//initial size constructor implementation
template <class T>
SafeArray <T> :: SafeArray(int initSize)
{
  //cout << "SafeArray initial size constructor called" << endl;

  //what if initSize = 0 or is negative?
  if(initSize <= 0)
    capacity = 10;
  else
    capacity = initSize;
    
  cout << "Array has been initialized with capacity of " << capacity << endl;

  //create new array of things on the heap
  p_array = new T[capacity];

  //initialize array position
  currentSize = initSize;
}

//copy ctor implementation
template <class T>
SafeArray <T> :: SafeArray(SafeArray <T> & otherArray)
{
  //cout << "SafeArray copy constructor called" << endl;
  
  //what if otherArray is empty?
  if(otherArray.size() == 0){
    capacity = 10;
    cout << "Since size of copy array was zero" <<
      " this array has been intialized with size 10" << endl;
  }
  else{
    //copy size of heap to that of otherArray
    capacity = otherArray.size();

    cout << "Array has been initialized with capcity equal to size of array copying from, size " << 
    otherArray.size() << endl;
  }

  //initialize our array of things
  p_array = new T[capacity];

  //initialize array position
  currentSize = 0;

  //copy array from otherArray into this object's array
  for(int i = 0; i < otherArray.size(); i++){
    push_back(otherArray.at(i));
  }

  
}

//destructor implementation
template <class T>
SafeArray <T> :: ~SafeArray()
{
  cout << "SafeArray destructor called" << endl;

  //delete memory allocated by this object
  delete [] p_array;
}

//push_back function implementation
template <class T>
void SafeArray <T> :: push_back(const T& element)
{
  //cout << "SafeArray push_back function called" << endl;
  
  //check to see if there is room for thing
  if(currentSize == capacity){
    
    //allocate more space
    cout << "Doubling Array from " << capacity <<
      " to " << capacity*2 << endl;
    T* p_arrayTemp = new T[capacity*2];

    //copy old array into first half of new array
    for(int i = 0; i < capacity; i++){
      p_arrayTemp[i] = p_array[i];
    }

    //update size of the array
    capacity = capacity * 2;

    //delete the old array from the heap
    delete [] p_array;

    //update where p_array points
    p_array = p_arrayTemp;
    
    //add latest word to array
    p_array[currentSize] = element;
  }
  else{
    //simply add the new element to the array
    p_array[currentSize] = element;
  }

    //update the array position
    currentSize++;
}

//push_back function for adding multiple elements to SafeArray
template <class T>
void SafeArray <T> :: push_back(const SafeArray <T>& newArray)
{
  //cout << "SafeArray push_back function for multiple elements called" << endl;

  //Dr. Mahoney's way, just saved me like 50 lines of code...hoorah
  for(int i = 0; i < newArray.size(); i++){
    push_back(newArray[i]);
  }
}

//pop_back function implementation
template <class T>
T SafeArray <T> :: pop_back()
{
  //cout << "SafeArray pop_back function called" << endl;

  //what if we are deleting last element of array?
  if(currentSize == 0){
    SafeArrayOutOfBoundsException error;
    throw error;
  }

  //get copy of last element
  T removed = p_array[currentSize];

  currentSize = currentSize - 1;

  //if currentSize is less than (capacity/2), halve capacity
  if((currentSize < (capacity/2)) && capacity != 1)
    resize(capacity/2);
 
  //return deleted element
  return removed;
  
}

//resize function implementation
template <class T>
void SafeArray <T> :: resize(int newSize)
{
  //cout << "SafeArray resize function called" << endl;

  //allocate space somewhere else for this size of array
  T* p_arrayTemp = new T[newSize];

  //copy old array into available spots of new array
  //have two possible cases
  
  //newSize is larger than old size
  if(newSize > capacity){
    for(int i = 0; i < currentSize; i++){
      p_arrayTemp[i] = p_array[i];
    }
  }
  //old size is larger than new size
  else{
    for(int i = 0; i < newSize; i++){
      p_arrayTemp[i] = p_array[i];
    }
  }

  //update size of the array
  capacity = newSize;

  cout << "Capacity has been changed to " << capacity << endl;

  //delete old array from heap
  delete [] p_array;

  //update wehre p_array points
  p_array = p_arrayTemp;

}

//at function implementation
template <class T>
T& SafeArray <T> :: at(int i) const
{
  //cout << "SafeArray at function called" << endl;

  //if the requested value is out of range
  if(i < 0 || i >= capacity){
    //bad value, throw exception
    SafeArrayOutOfBoundsException error;
    throw error;
  }
  else{
    //return the data at position i
    return p_array[i];
  }
}

//getCapacity function implementation
template <class T>
int SafeArray <T> :: getCapacity()
{
  //cout << "SafeArray getCapacity function called" << endl;

  return capacity;
}

//size function implementation
template <class T>
int SafeArray <T> :: size() const
{
  //cout << "SafeArray size function called" << endl;
  
  return currentSize;
}

//print function implementation
template <class T>
void SafeArray <T> :: print()
{
  //cout << "SafeArray print function called" << endl;

  if(currentSize == 0)
    cout << "This SafeArray is currently empty" << endl;

  for(int i = 0; i < capacity; i++){
    cout << i+1 << ". " << at(i) << endl;
  }
}

//operator overload [] implementation
template <class T>
T& SafeArray <T> :: operator[](int pos) const
{
  //cout << "SafeArray at function called" << endl;

  //call and return result of at function
  return at(pos);
}

//insert function implementation
template <class T>
void SafeArray <T> :: insert(int position, const T& element) 
{
  //cout << "SafeArray insert function called" << endl;

  if(position < 0 ||
     position > currentSize){
    SafeArrayOutOfBoundsException error;
    throw error;
  }
  
  //resize array capacity by one
  resize(capacity + 1);

  //push everything to the right of position, one element to the right
  for(int i = currentSize - 1; i >= position; i--){
    p_array[i+1] = p_array[i];
  }
  //put new element at position
  p_array[position] = element;
  
  //update currentSize of array
  currentSize++;
}

//insert SafeArray function implementation
template <class T>
void SafeArray <T> :: insert(int position, const SafeArray <T>& elements) 
{
  //cout << "SafeArray insert function for multiple elements called" << endl;

  for(int i = 0; i < elements.size(); i++){
    insert(position, elements.at(i));
    position++;
  }
}

//remove element function implementation
template <class T>
T SafeArray <T> :: remove(int position)
{
  //cout << "SafeArray remove function called" << endl;

  if(currentSize == 0){
    SafeArrayOutOfBoundsException error;
    throw error;
  }

  if(position > capacity){
    SafeArrayOutOfBoundsException error;
    throw error;
  }

  //create temp element variable to hold one removing
  T tempElement = at(position);

  //moving each element to the left one
  for(int i = position; i < currentSize - 1; i++){
    p_array[i] = p_array[i+1];
  }
  
  //adjust currentSize of array
  currentSize = currentSize - 1;

  //if currentSize is less then (capacity/2), halve capacity
  if((currentSize < (capacity/2)) && capacity != 1)
    resize(capacity/2);

  //remove last element
  return tempElement;
  
}

//remove range of elements function implementation
template <class T>
void SafeArray <T> :: removeRange(int startIndex, int endIndex)
{
  //cout << "SafeArray removeRange function called" << endl;
  for(int i = startIndex; i < endIndex; i++){
    remove(startIndex);
    //print();
  }
}

//remove by element, all occurrences of that element
template <class T>
bool SafeArray <T> :: removeElement(T element)
{
    bool retVal = false;

    if(currentSize == 0){
	SafeArrayOutOfBoundsException error;
	throw error;
    }

    for(int i = 0; i < currentSize; i++){

	if(at(i) == element){
	    remove(i);
	    retVal = true;
	}
    }


    //remove last element
    return retVal;
    

}
