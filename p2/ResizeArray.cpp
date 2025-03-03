/*
	CITATION:

	This is an adaptation of Mike's resizable array posted on LEARN.
*/
#include "declaration.hpp"
#include <iostream>
#include <string>
//constructor
resizableArray::resizableArray(int initCap)
{
	initCapacity = initCap;
	currentCapacity = initCap;
	size = 0;
	array = new std::string[initCap];
}

//destructor
resizableArray::~resizableArray()
{
	//std::cout<<"this run";
	delete[] array;
}

//get the size
int resizableArray::getSize()
{
	return size;
}

//get the size
int resizableArray::getCapacity()
{
	return currentCapacity;
}

//push adds an element to the start of the array, moving everything up, resizing if needed
void resizableArray::push(std::string word)
{
	//resize if needed
	if(size == currentCapacity - 1)
	{
		std::string* newAr = new std::string[currentCapacity*2];
		for(int i = 0; i < size; i++)
			newAr[i] = array[i];
		currentCapacity = currentCapacity*2;
		delete[] array;
		array = newAr;
	}
    //adding it to the back
    array[size]= word;
	//std::cout<<word<<" element"<<std::endl;
	size++;
}


//Get the element at the index but do not remove it
std::string resizableArray::getAt(int indx)
{
	if(indx < size){
		return array[indx];
	}
	else{
		return "UNKNOWN";
	}
}