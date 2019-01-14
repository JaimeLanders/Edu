#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

#include "data.h"
#include "linkedstack.h"
#include "linkedqueue.h"

data::data() // Data default constructor
{
	address = {'\0'};
	squareFeet = 0;
	roomCount = 0;
	bathCount = 0.0;
	notes = {'\0'};
}

data::data(const data& houseIn) // Data copy constructor
{
	setAddress(houseIn.address);
	setSquareFeet(houseIn.squareFeet);
	setRoomCount(houseIn.roomCount);
	setBathCount(houseIn.bathCount);
	setNotes(houseIn.notes);
}

data::~data() // Data deconstructor
{
		if (this->address)
		{
			delete[] this->address;
		}
		if (this->notes)
		{
			delete[] this->notes;
		}

      		this->squareFeet = 0;
		this->roomCount = 0;
		this->bathCount = 0.0;
}

const data& data::operator=(const data& houseIn)
{
	if (this != &houseIn)// && this != NULL)
	{
		setAddress(houseIn.address);
		setSquareFeet(houseIn.squareFeet);
		setRoomCount(houseIn.roomCount);
		setBathCount(houseIn.bathCount);
		setNotes(houseIn.notes);
	}
		return *this;
}

ostream& operator<<(ostream& outputStream, const data& houseIn)
{
	outputStream << houseIn.getAddress() << ", " ; 
	outputStream << houseIn.getSquareFeet() << ", " ; 
	outputStream << houseIn.getRoomCount() << ", " ; 
	outputStream << houseIn.getBathCount() << ", " ; 
	outputStream << houseIn.getNotes() << endl; 

	return outputStream;
}

void data::clear()
{
	if (this)// != NULL)	
	{
		address = {'\0'};
		delete[] this->address;
		this->squareFeet = 0;
		this->roomCount = 0;
		this->bathCount = 0.0;
		this->notes = {'\0'};
		delete[] this->notes;
	}

	return;
}


char* data::getAddress () const
{
	return address;
}

int data::getSquareFeet () const
{
	return squareFeet;
}

int data::getRoomCount () const
{
	return roomCount;
}

int data::getBathCount () const
{
	return bathCount;
}

char * data::getNotes () const
{
	return notes;
}

void data::setAddress(const char * tempStringIn)
{
	if (this->address)
		delete[] this->address;

	this->address = new char[strlen(tempStringIn)+1]; 
	strcpy(this->address, tempStringIn);
}

void data::setBathCount(float bathCountIn)
{
	bathCount = bathCountIn;
}

void data::setNotes(const char * tempStringIn)
{
	if (this->notes)
		delete[] this->notes; // Valgrind error

	this->notes = new char[strlen(tempStringIn)+1]; 
	strcpy(this->notes, tempStringIn);
}

void data::setRoomCount(int roomCountIn)
{
	roomCount = roomCountIn;
}

void data::setSquareFeet(int squareFeetIn)
{
	squareFeet = squareFeetIn;
}
