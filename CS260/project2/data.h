#ifndef data_h
#define data_h

using namespace std;

class data 
{
	char * address; // Stores adress
	int squareFeet; // Stores square footage
	int roomCount; // Stores number of rooms
	float bathCount; // Stores number of bathrooms
	char * notes; // Special notes/features about house
//	data * next; // Next pointer
public:
	data (); // Default constructor
	data (const data&  houseIn); // Copy constructor
	const data& operator=(const data&); // Assignment overload
	friend ostream& operator<<(ostream& outputStream, const data& houseIn); // Output stream overload
	~data (); // Deconstructor
	void clear (); // Clears data
	char* getAddress () const;
	int getSquareFeet () const;
	int getRoomCount () const;
	int getBathCount () const;
	data* getNext () const;
	char * getNotes () const;
	void setAddress (const char * tempStringIn);
	void setSquareFeet (int squareFeet);
	void setRoomCount (int roomCount);
	void setBathCount (float bathCount);
	void setNotes (const char * tempStringIn);
};

#endif
