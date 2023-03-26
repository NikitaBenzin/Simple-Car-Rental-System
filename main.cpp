#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstring>
#include <string>
#include <cctype>

using namespace std;

/*
	@ return bool 

	Login function:
	- return true if registration or login was ended successful
	- return false if registration or login failed
*/
bool login(void)
{
	string path = "Users.txt";

	fstream fsUser;
	bool validation = false;

	fsUser.open(path, fstream::in | fstream::out | fstream::app);

	if (!fsUser.is_open())
	{
		cout << "Connetion failed!" << endl;
	}
	else
	{
		// Variables
		string password, passwordBuff, value;
		

		// User registration / login
		system("cls");
		cout << "\n\n\n\tCAR RENTAL SYSTEM\n";
		cout << "\t-----------------------------------------------\n";
		cout << "\tInput the option: 1 Registration\t2 Login\n";
		cout << "\t-----------------------------------------------\n";
		cout << "\tInput: "; cin >> value;
		cout << endl << endl;

		// Registration
		if (value == "1")
		{
			system("cls");
			cout << "\n\n\n\tCAR RENTAL SYSTEM\n";
			cout << "\t-----------------------------------------------\n";
			cout << "\tREGISTRATION\n";
			cout << "\t-----------------------------------------------\n";
			cout << "\tCreate a password: "; cin >> password;
			cout << endl << endl;
			fsUser << password << "\n";
			validation = true;

			system("cls");
			Sleep(200);
			cout << "\n\n\n\tRegistration successful!\n\n";
			Sleep(2000);

		}
		// Login
		else if (value == "2")
		{
			system("cls");
			cout << "\n\n\n\tCAR RENTAL SYSTEM\n";
			cout << "\t-----------------------------------------------\n";
			cout << "\tLOGIN\n";
			cout << "\t-----------------------------------------------\n";
			cout << "\tEnter Password: "; cin >> password;
			cout << endl << endl;
			while (!fsUser.eof())
			{
				passwordBuff = "";
				fsUser >> passwordBuff;

				if (passwordBuff == password) validation = true;
			}
			if (validation == true)
			{
				system("cls");
				Sleep(200);
				cout << "\n\n\n\tLogin successful!\n\n";
				Sleep(2000);
			} 
			else 
			{
				system("cls");
				Sleep(200);
				cout << "\n\n\n\tLogin Failed!\n\n";
				Sleep(2000);
			}
		}
		else
		{
			system("cls");
			cout << "\n\n\n\tInvalid input\n\n";
			Sleep(2000);
		}

	}
	fsUser.close();
	return validation;
}

/*
	@ return void

	Car Select function:
	- Return Username, Car code and Car Number
*/
string carSelect(void) 
{
	// Variables
	fstream car;
	car.open("Cars.txt", fstream::in | fstream::out | fstream::app);
	string username;
	string input, carNumber, carNumberBuff, carCode, carName, carModel;
	char buff;
	bool validation = false;

	if (!car.is_open())
	{
		system("cls");
		cout << "\n\tFailed Connection...\n\n";
	}
	else
	{

		system("cls");
		cout << "\n\n\n\tPlease Enter your Name: "; cin >> username;
		cout << "\n\tPlease Select a Car:\n";
		while (!car.eof())
		{
			car >> carCode;
			car >> carName;
			car >> carModel;
			cout << "\tEnter '" + carCode + "' for " + carName + " " + carModel + "\n";
		}
		cout << "\tChoose a Car: "; cin >> input;
		car.close();

		// To upper case the input
		buff = toupper(input[0]);
		input = buff;

		// What the car
		car.open("Cars.txt", fstream::in | fstream::out | fstream::app);
		while (!car.eof())
		{
			car >> carCode;
			car >> carName;
			car >> carModel;
			if (carCode == input)
			{
				validation = true;
				system("cls");
				cout << "\n\n\n\tYou have choosed "+ carName + " model " + carModel + "\n";
			}
		}

		// Asking a car number
		if (validation == true)
		{
			cout << "\t--------------------------------------------\n";
			cout << "\tPlease provide following information:\n";
			cout << "\tSelect a Car No. : "; cin >> carNumberBuff;
			cout << endl << endl;

			if (carNumberBuff.size() > 4)
			{
				for (int i = 0; i < 4; i++)
				{
					carNumber += carNumberBuff[i];
				}
			}
			else if (carNumberBuff.size() < 4) 
			{
				for (int i = 0; i < 4; i++)
				{
					buff = rand() % 127;
					if (isalnum(buff))
					{
						carNumber += buff;
					}
					else --i;
				}
			}
			else carNumber = carNumberBuff;
		}
		else
		{
			cout << "\n\n\n\tInvalid input";
		}
	}
	car.close();
	return input + carNumber + username;
}

/*
	@ return bool

	Rent Calculator:
	- Ask number of days
	- Return total cost of rent
*/
bool rentCalculator(string carCode, string carNumber, string username)
{
	// Variables
	string invoiceNumber, scost, costBuff, carCodeBuff;
	fstream rentCost;
	short numOfDays = 0;
	int intCost, totalRent = 1;
	char buff;
	bool validation = false;

	rentCost.open("RentCost.txt", fstream::in | fstream::out | fstream::app);

	if (!rentCost.is_open())
	{
		system("cls");
		cout << "\n\tFailed Connection...\n\n";
	}
	else
	{
		system("cls");
		cout << "\n\tNumber of days: "; cin >> numOfDays;

		// Check a number of days
		if (numOfDays == 0)
		{
			cout << "\n\tInvalid input!";
			validation = true;
		}
		else
		{
			validation = true;
			system("cls");
			cout << "\n\tCalculating rent. Please wait...\n\n";
			Sleep(2000);

			// Read a rent cost
			while (!rentCost.eof())
			{
				rentCost >> carCodeBuff;
				rentCost >> costBuff;
				if (carCode == carCodeBuff)
				{
					scost = costBuff;
				}
			}
			// Convert string to int 
			intCost = stoi(scost);

			// Create invoice no.
			for (short i = 0; i < 8; i++)
			{
				buff = rand() % 127;
				if (isalnum(buff))
				{
					invoiceNumber += buff;
				}
				else --i;
			}
			totalRent = numOfDays * intCost;

			// Rent cout
			cout << "\t\tCar Rental - Custom Invoice\n";
			cout << "\t////////////////////////////////////////";
			cout << "\n\t| Invoice No. :\t\t" << invoiceNumber;
			cout << "\n\t| Customer Name :\t" << username;
			cout << "\n\t| Car code :\t\t" << carCode;
			cout << "\n\t| Car number :\t\t" << carNumber;
			cout << "\n\t| Number of days :\t" << numOfDays;

			cout << "\n\n\t---------------------------------------\n";
			cout << "\n\t| Total Rent Amount is :\t" << totalRent;
			cout << "\n\n\t---------------------------------------\n";

		}
	}
	rentCost.close();
	return validation;
}


// ----------- MAIN ---------- //
int main()
{
	srand(time(0));

	bool toggleLogin = false, toggleRent = false;
	string carCode, carNumber, username, information;

	// Login loop
	while (toggleLogin == false)
	{
		toggleLogin = login();
	}

	if (toggleLogin == true)
	{
		information = carSelect();
		cout << information;
		carCode = information[0];
		for (int i = 1; i < information.size(); i++)
		{
			if (i <= 4) carNumber += information[i];
			else if (i > 4) username += information[i];
		}

		while (toggleRent == false)
		{
			toggleRent = rentCalculator(carCode, carNumber, username);
		}
	}

	return 0;
}