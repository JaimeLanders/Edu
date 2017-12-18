#include <cstdlib>
#include <ctime>
#include <iostream>

void photon (int& currentHp, int& photonShot, int& photonMiss);
void torpedo (int& currentHp, int& torpShot, int& torpMiss);

const int botHp = 100;

using namespace std;

int main ()
{
	srand(time(NULL));

	char selection; 
	int currentHp, photonDmg, photonShot, photonMiss = 0;
	int torpDmg, torpShot, torpMiss = 0;
	
//	torpMiss = 0;

//	cout << photonMiss << endl;
		
	currentHp = botHp;

	cout << "Drone released for targer practice... " << endl;

	do
	{
		cout << "The bot's current HP is: " << currentHp << ". " << endl;
		cout << "What would you like to do? Enter (p)hoton, (t)orpedo, or (q)uit: " << endl;
		cin >> selection;
//		cout << selection << endl;

		if (selection == 'p')
			photon(currentHp, photonShot, photonMiss); 
		else if (selection == 't')
			torpedo(currentHp, torpShot, torpMiss); 
		else if (selection == 'q')
			cout << "Goodbye" << endl;
		else
			cout << "You did not enter a valid choice, try again... " << endl;
	}
	while (selection != 'q' && currentHp > 0);

	if (currentHp <= 0)
	{
		cout << "======================== " << endl;
		cout << "The drone was destroyed! " << endl;
       		cout << photonShot << " photon shots hit, and " << photonMiss << " shots missed. " << endl;  
       		cout << torpShot << " torpedo shots hit, and " << torpMiss << " shots missed. " << endl;  
	}

	return 0;
}
 
void photon(int& currentHp, int& photonShot, int& photonMiss)
{
	bool hitConf = 0;
	int hitPer, photonDmg = 0;

//	cout << photonMiss << endl;
	cout << "Firing Photon..." << endl;
	 
	photonDmg = rand () % 16 + 15;
//	cout << photonDmg << endl;

	hitPer = rand () % 100 + 1;
//	cout << hitPer << endl;
//
	if (hitPer < 75)
	{
		hitConf = 0;
		cout << "Photon missed... " << endl;
		photonMiss++;
//		cout << photonMiss << endl;
		photonDmg = 0 ;
	}
	else 
	{
		hitConf = 1;
		cout << "Photon hit! " << endl;
		photonShot++;
//		cout << photonShot << endl;
	}          	

	cout << "Photon did " << photonDmg << " damage. " << endl;

	currentHp -= photonDmg;
}

void torpedo(int& currentHp, int& torpShot, int& torpMiss)
{
	bool hitConf = 0;
	int hitPer, torpDmg = 0;

//	cout << torpMiss << endl;
	cout << "Firing Torpedo..." << endl;
	 
	torpDmg = rand () % 16 + 35;
//	cout << torpDmg << endl;

	hitPer = rand () % 100 + 1;
//	cout << hitPer << endl;
//
	if (hitPer < 50)
	{
		hitConf = 0;
		cout << "Torpedo missed..." << endl;
		torpMiss++;
//		cout << torpMiss << endl;
		torpDmg = 0 ;
	}
	else 
	{
		hitConf = 1;
		cout << "Torpedo hit!" << endl;
		torpShot++;
//		cout << torpShot << endl;
	}          	

	cout << "Torpedo did " << torpDmg << " damage. " << endl;

	currentHp -= torpDmg;
}
