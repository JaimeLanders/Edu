#include <iostream>

using namespace std;

int main ()
{
	char intLife, warpTech = 'n';
	double planetDi, starDis = 0.0; 

	cout << "Computer.  Working.  What is the distance of the planet from it's star (in millions of miles)? " << endl; 
	cin >> starDis;
//	cout << starDis << endl;
	if (starDis < 75)
	{
		cout << "The planet is too close too it's star and the planet is too hot too be habitable. " << endl;
		cout << "Analysis complete, program terminated. " << endl;
		return 0;
	}
	else if (starDis >= 75 && starDis <= 110)
		cout <<"The planet is in the habitable zone. " << endl;
	else if (starDis > 110)
	{
		cout << "The planet is too far away from it's star and is too cold to be habitable. " << endl;		
		cout << "Analysis complete, program terminated. " << endl;
		return 0;
	}			

	cout << "What is the diameter of the planet (in miles)? " << endl;
	cin >> planetDi;
//	cout << planetDi << endl;
	if (planetDi < 5000)
	{
		cout << "The planet is too small to be habitable. " << endl;
		cout << "Analysis complete, program terminated. " << endl;
       		return 0;	
	}
	else if (planetDi >= 5000 && planetDi <= 10000)
		cout << "Based on the distance and gravitational pull, the planet may be suitable for human life. " << endl;
	else if (planetDi > 10000)
	{
		cout << "The planet is too big for human habitation. " << endl;
		cout << "Analysis complete, program terminated. " << endl;
		return 0;
	}

	cout << "Is there intelligent life detected on the planet (y/n)? " << endl;
	cin >> intLife;
//	cout << intLife << endl;	
	if (intLife == 'n')
	{
		cout << "There is no life on the planet so it may be suitable for colonization. " << endl;
		cout << "Analysis complete, program terminated. " << endl;
       		return 0;		
	}
	else if (intLife == 'y')
	{
		cout << "Does the intelligent life have warpdrive technology (y/n)? " << endl;  
		cin >> warpTech;
//		cout << warpTech; 
		if (warpTech == 'y')
		{
			cout << "Since the intelligent life has warpdrive technology, you may make first contact.  Proceed with caution. " << endl;
			cout << "Analysis complete, program terminated. " << endl;
			return 0;
		}
		else if (warpTech == 'n')
		{
			cout << "Obey the prime directive, do not make contact. " << endl;
			cout << "Analysis complete, program terminated. " << endl;
			return 0;
		}
	}

	return 0;
}
