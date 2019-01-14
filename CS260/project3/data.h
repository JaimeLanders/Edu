#ifndef DATA_H 
#define DATA_H 

#include <iostream>

using namespace std;

class data
{
	float assetValue;
	char * dateValue;
	char * stockName;
	char * tickerSymbol;
	float ytdReturn;
public:
	data ();
	data (const data& dataIn);
	~data ();
	const data& operator=(const data& dataIn);
	friend ostream& operator<< (ostream& out, const data& dataIn);
	void getDate (char * dateValue) const;
	void getName (char * stockName) const;
	float getReturn (void) const;
	void getTicker (char * tickerSymbol) const;
	float getValue (void) const;
	bool setDate (const char * dateIn);
	bool setName (const char * nameIn);
	bool setReturn (const float returnIn);
	bool setTicker (const char * tickerIn);
	bool setValue (const float valueIn);
};

#endif
