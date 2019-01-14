#ifndef DATA_H
#define DATA_H
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class data
{
	char * vendorName;
	char * phoneNumber;
	char * productType;
	char * eventNotes;  
public:
	data();
	data(const data& dataIn);
	data(char * vendorNameIn, char * phoneNumberIn, char * productTypeIn, char * eventTypeIn);
 	data& operator=(const data& dataIn);
 	friend ostream& operator<< (ostream& out, const data& dataIn);
	~data();
	void clear();
	void getName(char * nameIn)const;
	int getNumber(char * numIn)const;
	void getProduct(char * typeIn)const;
	void getEvents(char * eventIn)const;
	void setName(const char * nameIn);
	void setNumber(const char * numIn);
	void setProduct(const char * typeIn);
	void setEvents(const char * eventIn);
};

#endif
