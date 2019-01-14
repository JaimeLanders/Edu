#include <cstring>
#include <iomanip>
#include <iostream>
#include "data.h"

using namespace std;

data::data ()
{
	tickerSymbol = {'\0'};
	stockName = {'\0'};
	assetValue = 0.0;
	dateValue = {'\0'};
	ytdReturn = 0.0;
} 

data::~data ()
{
	if (tickerSymbol)
		delete [] tickerSymbol; // Valgrind: Invalid read error
	if (stockName)
		delete [] stockName;
	if (dateValue)
		delete [] dateValue;
} 

data::data(const data& dataIn)
{
	setTicker(dataIn.tickerSymbol);
	setName(dataIn.stockName);
	setValue(dataIn.assetValue);
	setDate(dataIn.dateValue);
	setReturn(dataIn.ytdReturn);
}

const data& data::operator=(const data& dataIn)
{
	if (this != &dataIn)
	{
		setTicker(dataIn.tickerSymbol);
		setName(dataIn.stockName);
		setValue(dataIn.assetValue);
		setDate(dataIn.dateValue);
		setReturn(dataIn.ytdReturn);
	}

	return *this;
}

ostream& operator<< (ostream& out, const data& dataIn)
{

out << showpoint << setprecision(4) << dataIn.tickerSymbol << "\t\t" << dataIn.stockName << "\t" << "$" << dataIn.assetValue << "\t"<< dataIn.dateValue << "\t" << dataIn.ytdReturn << "%" << endl;
	return out;
}

void data::getDate (char * dateValue) const
{

	strcpy(dateValue, this->dateValue);
}

void data::getName (char * stockName) const
{
	strcpy(stockName, this->stockName);
}

float data::getReturn (void) const
{
	return ytdReturn;
}

void data::getTicker (char * tickerSymbol) const
{
	strcpy(tickerSymbol, this->tickerSymbol);
}

float data::getValue (void) const
{
	return assetValue;
}

bool data::setDate (const char * dateIn)
{
	if (this->dateValue)
	{
		delete [] this->dateValue;
	}

	dateValue = new char[strlen(dateIn)+1]; 
	strcpy (dateValue, dateIn);	

	return 0;
}

bool data::setName (const char * nameIn)
{
	if (this->stockName)
	{
		delete [] this->stockName;
	}

	stockName = new char[strlen(nameIn)+1]; 
	strcpy (stockName, nameIn);	

	return 0;
}

bool data::setReturn (const float returnIn)
{
	ytdReturn = returnIn;

	return 0;
}

bool data::setTicker (const char * tickerIn)
{
	if (this->tickerSymbol)
	{
		delete [] this->tickerSymbol;
	}

	this->tickerSymbol = new char[strlen(tickerIn)+1]; 
	strcpy (this->tickerSymbol, tickerIn);	

	return 0;
}

bool data::setValue (const float valueIn)
{
	assetValue = valueIn;

	return 0;
}
