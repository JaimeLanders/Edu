#include "project1.h" 

wineryInfo::wineryInfo()
{
	wineryName = NULL;
	wineryLocale = NULL;
	wineryYear = 0;
	wineryAcres = 0;
	wineryRating = 0;
	nextName = NULL;
	nextRating = NULL;
}

wineryInfo::wineryInfo(const wineryInfo& source )
{
	cout << "wineryInfo Copy Constructor " << endl;

}

wineryInfo& wineryInfo::operator=(const wineryInfo& source)
{
	cout << "wineryInfo overloaded = operator " << endl;
}

wineryOps::wineryOps()
{
	nameHead = NULL;
	rateHead = NULL;
}

wineryOps::wineryOps(const wineryOps& source)
{
	wineryInfo * curChain;
	curChain = nameHead;

	if (curChain == NULL)
	{
		nameHead = NULL;
		rateHead = NULL;

		return;
	}
	else
	{
		nameHead = new wineryInfo();    
		nameHead->nextName = curChain->nextName;
		rateHead->nextRating = curChain->nextRating;

		wineryInfo * curChain;
		wineryInfo * newChain;
		curChain = curChain->nextName;
		newChain = nameHead;

		while (curChain != NULL)
		{
			wineryInfo *nextName = curChain->nextName;
			wineryInfo *nextRating = curChain->nextRating;
			wineryInfo * n;
			n = new wineryInfo;

			newChain = newChain->nextName;
			curChain = curChain->nextName;
		}

		newChain->nextName = NULL;
	}

}

wineryOps& wineryOps::operator=(const wineryOps& source)
{
	if (this != &source)
	{
		wineryInfo * current; 
		current = nameHead;

		while (current != NULL)
		{
			current = current->nextName;
			delete nameHead;
			nameHead = current;
		}

		if (source.nameHead == NULL)
		{
			nameHead = NULL;
			rateHead = NULL;
		}
		else
		{
			nameHead = new wineryInfo;

			nameHead->wineryLocale = source.nameHead->wineryLocale;
			nameHead->wineryYear = source.nameHead->wineryYear;
			nameHead->wineryAcres = source.nameHead->wineryAcres;
			nameHead->wineryRating = source.nameHead->wineryRating;
			nameHead->wineryName = source.nameHead->wineryName;
			nameHead->nextName = source.nameHead->nextName;
			nameHead->nextRating = source.nameHead->nextRating;

			wineryInfo * source;
			current = nameHead;
			source = source->nextName;

			while (source != NULL)
			{
				current->nextName = new wineryInfo; 

				current = current->nextName;

				current->wineryLocale = source->wineryLocale;
				current->wineryYear = source->wineryYear;
				current->wineryAcres = source->wineryAcres;
				current->wineryRating = source->wineryRating;
				current->wineryName = source->wineryName;
				current->nextName = source->nextName;
				current->nextRating = source->nextRating;

				source = source->nextName;

			}

			current->nextName = NULL;
		}
	}

	       return *this;	

}

wineryOps::~wineryOps()
{
	wineryInfo * current;
	wineryInfo * previous;
	current = nameHead;
	previous = NULL;

	while (current != NULL)
	{
		delete[] current->wineryName;
		delete[] current->wineryLocale;
		previous = current;
		current = current->nextName;
		delete previous;
	}

}

void wineryOps::addWinery(wineryInfo * n)
{
	wineryInfo * current;
	wineryInfo * previous;
	current = NULL;
	previous = NULL;

	if (rateHead == NULL)
	{
	       	rateHead = n;	
	       	rateHead->nextRating = NULL;
	}
	else if (rateHead->wineryRating < n->wineryRating)
	{
		n->nextRating = rateHead;
		rateHead = n; 
	}
	else
	{
		current = rateHead;
		previous = rateHead; 

		while (current != NULL)
		{
			if (current->wineryRating < n->wineryRating)
			{
				previous->nextRating = n;
				n->nextRating = current;
				break;		
			}
			else if (current->nextRating == NULL)
			{
				current->nextRating = n;
				n->nextRating = NULL;
				break;
			}
			else 
			{
				previous = current;
				current = current->nextRating;
			}

		}

	}

	if (nameHead == NULL)
	{
	       	nameHead = n;	
	       	nameHead->nextName = NULL;
	}
	else if (strcmp (n->wineryName,nameHead->wineryName) < 0 )
	{
		n->nextName = nameHead;
		nameHead = n; 
	}
	else
	{
		current = nameHead;
		previous = nameHead;

		while (current != NULL)
		{
			if (strcmp (n->wineryName,current->wineryName) < 0 )
			{
				previous->nextName = n;
				n->nextName = current;
				break;		
			}
			else if (current->nextName == NULL)
			{
				current->nextName = n;
				n = NULL;
				break;
			}
			else
			{
				current = current->nextName;
			}
		}
	}

	return;
}

void wineryOps::deleteWinery(char delName[STRINGSIZE])
{
	wineryInfo * current;
	wineryInfo * previous;
	current = NULL;
	previous = NULL;

	bool nameDeleted = false;

	if (strcmp (nameHead->wineryName,delName) == 0 && strcmp (nameHead->wineryName,delName) != 0)
	{
		current = nameHead;
		nameHead = nameHead->nextName;
		delete[] current->wineryName;
		delete[] current->wineryLocale;
		delete current;

		nameDeleted = true;
	}
	else if (strcmp (rateHead->wineryName,delName) == 0 && strcmp (rateHead->wineryName,delName) != 0)
	{
		current = rateHead;
		rateHead = rateHead->nextRating;
		delete[] current->wineryName;
		delete[] current->wineryLocale;
		delete current;

		nameDeleted = true;
	}
	else if (strcmp (rateHead->wineryName,delName) == 0 && strcmp (rateHead->wineryName,delName) == 0)
	{
		current = nameHead;
		nameHead = nameHead->nextName;
		rateHead = rateHead->nextRating;
		delete[] current->wineryName;
		delete[] current->wineryLocale;
		delete current;

		nameDeleted = true;
	}
	else
	{
		current = nameHead;
		previous = nameHead;

		while (current != NULL)
		{
			if (strcmp (current->wineryName,delName) == 0 )
			{
				previous->nextName = current->nextName;
				previous->nextRating = current->nextRating;

				delete[] current->wineryName;
				delete[] current->wineryLocale;
				delete current;

				nameDeleted = true;

				break;

			}
			else if (current->nextName == NULL)
			{
				previous->nextName = NULL;

				delete[] current->wineryName;
				delete[] current->wineryLocale;
				delete current;
				nameDeleted = true;

				break;
			}
			else
			{
				previous = current;
				current = current->nextName;
			} // Closes else
			
		}  // Closes while
		
	
	} // Closes else

	if (current == NULL && nameDeleted == false)
	{
		cout << delName << " not found... " << endl;
	}

	return;
}

void wineryOps::loadFile()
{
	ifstream inFile;
	inFile.open(FILENAME);
	inFile.peek();

	char charEat = '\0';
	char tempName[STRINGSIZE] = {'\0'};
	char tempLocale[STRINGSIZE] = {'\0'};
	int nameSize = 0;
	int townSize = 0;

	while (!inFile.fail() && !inFile.eof())
	{
		wineryInfo * n = NULL;
		n = new wineryInfo;

		inFile.getline(tempName, STRINGSIZE, ',');
		nameSize = strlen(tempName);
		n->wineryName = new char[nameSize + 1];
		strncpy(n->wineryName, tempName, nameSize);
		n->wineryName[nameSize] = '\0';

		inFile.getline(tempLocale, STRINGSIZE, ',');
		townSize = strlen(tempLocale);
		n->wineryLocale = new char[townSize + 1];
		strncpy(n->wineryLocale, tempLocale, townSize);
		n->wineryLocale[townSize] = '\0';

		inFile >> n->wineryYear;
		inFile >> charEat;
		inFile >> n->wineryAcres;
		inFile >> charEat;
		inFile >> n->wineryRating;
		inFile.ignore();

		inFile.peek();

		addWinery(n);
	}
	
	inFile.close();

	return;

}

void wineryOps::saveFile()
{

	ofstream outFile;
	outFile.open(FILENAME);

	wineryInfo * current;
	current = nameHead;

	int stringSize = 0;
	char tempString[STRINGSIZE] = {'\0'};

	while (current != NULL)
	{
		outFile << current->wineryName << ",";
		outFile << current->wineryLocale << ",";
		outFile << current->wineryYear << ",";
		outFile << current->wineryAcres << ",";
		outFile << current->wineryRating << endl;

		current = current->nextName;
	}

	outFile.close();

	return;
}

void wineryOps::viewByName()
{
	wineryInfo * current;   
	current = nameHead;

	while (current != NULL)
	{
		cout << "\nWinery Name: \t\t" << current->wineryName << endl;
		cout << "Winery Location: \t" << current->wineryLocale << endl;
		cout << "Winery Established: \t" << current->wineryYear << endl;
		cout << "Winery Acres: \t\t" << current->wineryAcres << endl;
		cout << "Winery Rating: \t\t" << current->wineryRating << endl;
		cout << "\n===== " << endl;

		current=current->nextName;
	}

	return;
}

void wineryOps::viewByRating()
{
	wineryInfo * current;   
	current = rateHead;

	while (current != NULL)
	{
		cout << "\nWinery Name: \t\t" << current->wineryName << endl;
		cout << "Winery Location: \t" << current->wineryLocale << endl;
		cout << "Winery Established: \t" << current->wineryYear << endl;
		cout << "Winery Acres: \t\t" << current->wineryAcres << endl;
		cout << "Winery Rating: \t\t" << current->wineryRating << endl;
		cout << "\n===== " << endl;

		current=current->nextRating;
	}

	return;
}

void wineryOps::searchName(char searchName[STRINGSIZE])
{
	wineryInfo * current;
	current = nameHead;

	bool nameFound = false;

	while (current != NULL)
	{
		if (strcmp (current->wineryName,searchName) == 0)
		{
			nameFound = true;

			break;
		}
		else
		{
			current = current->nextName;
		}
	}

	if (nameFound == true)
	{
		cout << "\nWinery Name: \t\t" << current->wineryName << endl;
		cout << "Winery Location: \t" << current->wineryLocale << endl;
		cout << "Winery Established: \t" << current->wineryYear << endl;
		cout << "Winery Acres: \t\t" << current->wineryAcres << endl;
		cout << "Winery Rating: \t\t" << current->wineryRating << endl;
		cout << "\n===== " << endl;
	}
	else
	{
		cout << searchName << " not found.. " << endl;
	}


	return;
}
