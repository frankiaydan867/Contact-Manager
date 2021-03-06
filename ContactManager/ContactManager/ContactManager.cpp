#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <mysql.h>
#include "ProgramFunctions.h"

using namespace std;



int main()
{
	int menu_selection;
	bool isValidUser = false;
	string userid;

	
	/*
	Username: admin
	Password: admin
	*/
	LoginScreen(userid, isValidUser);
	
	//Refresh the screen
	ClearScreen();
	

	//Menu
	MAIN_MENU:
	MainMenu();
	cin >> menu_selection;

		switch (menu_selection) {
			case 0:
				ClearScreen();
				cout << "Bye!";
				break;
			//Add Contact
			case 1:
				AddContact();
				goto MAIN_MENU;
			//Update Contact
			case 2:
				UpdateContact();
				goto MAIN_MENU;
			//View Contact
			case 3:
				ViewContact();
				goto MAIN_MENU;
			//Add Log
			case 4:
				AddLog();
				goto MAIN_MENU;
			//Reports
			case 5:
				Report();
				goto MAIN_MENU;
			//Print Contact to File
			case 6:
				PrintToFile();
				goto MAIN_MENU;
			//Settings
			default:
				cout << "\nInvalid Entry\n";
				Sleep(1000);
				goto MAIN_MENU;
		}

	cin.ignore();
	getchar();

	return 0;
}

