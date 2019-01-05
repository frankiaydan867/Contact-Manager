#pragma once
#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <mysql.h>
#include <fstream>
#include "Contact.h"

using namespace std;

//To test methods
void Test() {
	cout << "another test";
}

//Database transactions template
void DBTransaction() {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		puts("Connected to DB!");

		string query = "Select FirstName,LastName FROM contact";

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res))
		{
			cout << "test: " << row[0] << row[1];
		}

	}
}

//******************************Database Functions**********************
//Get credentials
void GetCredentialsFromDB(string user, string pass, bool (&found), string (&id)) {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;

	//found = false;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		//puts("\nSearching");

		string query = "Select ID, Username, Password FROM users "
			"WHERE Username = '" + user + "' AND Password = '" + pass + "'";

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		res = mysql_store_result(con);
		if (row = mysql_fetch_row(res))
		{
			found = true;
			id = row[0];
		}
		

	}
}

void PullLastID(int(&id)) {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;
	string n;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		string query = "Select MAX(ID) FROM contact";			

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		res = mysql_store_result(con);
		if (row = mysql_fetch_row(res))
		{
			n = row[0];
			id = stoi(n);
		}
	}
}

void LastNote(int(&id)) {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;
	string n;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		string query = "Select MAX(CommID) FROM communicationlog";

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		res = mysql_store_result(con);
		if (row = mysql_fetch_row(res))
		{
			n = row[0];
			id = stoi(n);
		}
	}
}

void FindContactToUpdate(int id, bool(&f), Contact(&co)) {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;
	string n;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		string query = "Select * FROM contact WHERE ID = " + to_string(id);

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		res = mysql_store_result(con);
		if (row = mysql_fetch_row(res))
		{
			f = true;
			co.setID(stoi(row[0]));
			co.setFirstName(row[1]);
			co.setLastName(row[2]);
			co.setEmail(row[3]);
			co.setPhone(row[4]);
			co.setAddress(row[5]);
			co.setCity(row[6]);
			co.setState(row[7]);

		}
		else {
			f = false;
		}
	}
}

void UpdateContactOnDB(int field, string newvalue, int id, bool(&save)) {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;
	string n;
	string tablefield;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	switch (field) {
		case 1:
			tablefield = "FirstName";
		case 2:
			tablefield = "LastName";
		case 3:
			tablefield = "Email";
		case 4:
			tablefield = "Phone";
		case 5:
			tablefield = "Address1";
		case 6:
			tablefield = "City";
		case 7:
			tablefield = "State";
	}

	if (con) {
		string query = "UPDATE contact SET " + tablefield +
			" = '" + newvalue + "' WHERE ID = " + to_string(id);

		const char* q = query.c_str();
		qstate = mysql_query(con, q);
		save = true;
	}
}

void AddContactToDB(Contact co) {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;
	string n;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		string query = "INSERT INTO contact VALUES (" +
			to_string(co.getID()) + ",'" +
			co.getFirstName() + "','" +
			co.getLastName() + "','" +
			co.getEmail() + "','" +
			co.getPhone() + "','" +
			co.getAddress() + "','" +
			co.getCity() + "','" +
			co.getState() + "')";
		
		const char* q = query.c_str();
		qstate = mysql_query(con, q);
	}
}

void FindContact(int id, bool (&f), string(&cname)) {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;
	string n;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		string query = "Select ID, CONCAT(FirstName,' ',LastName) AS name FROM contact WHERE ID =" + to_string(id);

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		res = mysql_store_result(con);
		if (row = mysql_fetch_row(res))
		{
			f = true;
			cname = row[1];
		}
		else {
			f = false;
		}
	}
}

void DisplayLogs(int id) {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		string query = "SELECT * FROM communicationlog WHERE CustomerID = " + to_string(id);

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res))
		{
			cout << row[3] << "\n---------------------------\n";
			cout << row[2];
			cout << "\n\n";
		}

	}
}

void SaveLog(string log, int contactid, int logid) {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;
	string n;

	//Add one to have the next note id
	logid++;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		string query = "INSERT INTO communicationlog VALUES (" + to_string(logid) +
			", " + to_string(contactid) + ", '" + log +"', CURRENT_TIMESTAMP)";
			 

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		
	}
}

void PrintAllContacts() {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;

	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		string query = "Select * FROM contact";

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		res = mysql_store_result(con);
		cout << left << setw(5) << "ID"
			<< left << setw(15) << "First Name"
			<< left << setw(15) << "Last Name"
			<< left << setw(25) << "Email"
			<< left << setw(15) << "Phone"
			<< left << setw(30) << "Address"
			<< left << setw(25) << "City"
			<< left << setw(15) << "State" << endl;
			
		for (int l = 0; l < 135; l++) {
			cout << "-";
		}
		cout << endl;

		while (row = mysql_fetch_row(res))
		{
			cout << left << setw(5) << row[0]
				<< left << setw(15) << row[1]
				<< left << setw(15) << row[2]
				<< left << setw(25) << row[3]
				<< left << setw(15) << row[4]
				<< left << setw(30) << row[5]
				<< left << setw(25) << row[6]
				<< left << setw(15) << row[7] << endl;
		}
		cout << endl;

	}
}

void PrintAllContactsToFile() {
	MYSQL* con; //Connection
	MYSQL_ROW row; //Record
	MYSQL_RES *res;
	con = mysql_init(0);
	int qstate;

	ofstream file;


	//Connection
	con = mysql_real_connect(con, "localhost", "root", "admin", "contact_manager", 3306, NULL, 0);

	if (con) {
		string query = "Select * FROM contact";

		const char* q = query.c_str();
		qstate = mysql_query(con, q);

		res = mysql_store_result(con);
		
		file.open("C:\Contact Manager Report - " + to_string(time(0)) + ".txt");
		//file.open("C:\Contact Manager Report - .txt");
		file << left << setw(5) << "ID"
			<< left << setw(15) << "First Name"
			<< left << setw(15) << "Last Name"
			<< left << setw(25) << "Email"
			<< left << setw(15) << "Phone"
			<< left << setw(30) << "Address"
			<< left << setw(25) << "City"
			<< left << setw(15) << "State" << endl;

		for (int l = 0; l < 135; l++) {
			file << "-";
		}
		file << endl;

		while (row = mysql_fetch_row(res))
		{
			file << left << setw(5) << row[0]
				<< left << setw(15) << row[1]
				<< left << setw(15) << row[2]
				<< left << setw(25) << row[3]
				<< left << setw(15) << row[4]
				<< left << setw(30) << row[5]
				<< left << setw(25) << row[6]
				<< left << setw(15) << row[7] << endl;
		}
		file << endl;

	}
}

//*********************************************************************

//Clear screen
void ClearScreen() {
	system("cls");
}

//Draw a line passing the lenght as value
void DrawLine(int l) {
	for (int i = 0; i < l; i++) {
		cout << "-";
	}
	cout << endl;
}

//Login screen
void LoginScreen(string (&ID),bool (&vu)) {

	//bool found = false; //To check if user exists
	
	LOGIN:
	ClearScreen();

	DrawLine(21);
	cout << "\tLogin\n";
	DrawLine(21);

	string username;
	string password;

	cout << "Username: ";
	cin >> username;

	cout << "Password: ";
	cin >> password;

	GetCredentialsFromDB(username, password, vu, ID);

	if (vu) {
		ClearScreen();
		cout << "Welcome " << username << "!";
		Sleep(1000);
	}
	else {
		cout << "\nInvalid Login! Please try again...\n\n";
		Sleep(1000);
		goto LOGIN;

	}
}

//Program Title
void ProgramTitle() {
	cout << "*********************************\n";
	cout << "\tContact Manager\n";
	cout << "*********************************\n";
}


//**************************Menu Functions****************************
//Main Menu
void MainMenu() {
	ProgramTitle();
	
	cout << "\nMain Menu\n----------------------\n";
	cout << "1 - Add Contact\n";
	cout << "2 - Update Contact\n";
	cout << "3 - View Contact\n";
	cout << "4 - Add Log\n";
	cout << "5 - Reports\n";
	cout << "6 - Print Contact to File\n";
	cout << "0 - Exit\n";
	cout << "\nPlease make a selection: ";
}

//Add Contact
void AddContact() {
	ClearScreen();

	Contact c;
	int intinput;
	string strinput;
	int nextid;

	PullLastID(nextid);
	nextid++;

	cout << "Add Contact\n---------------------\n\n";
	cout << "New ID: " << nextid << endl;
	c.setID(nextid);
	
	cout << "First Name: ";
	cin >> strinput;
	c.setFirstName(strinput);

	cout << "Last Name: ";
	cin >> strinput;
	c.setLastName(strinput);

	cout << "Email: ";
	cin >> strinput;
	c.setEmail(strinput);
	
	cout << "Phone: ";
	cin >> strinput;
	c.setPhone(strinput);
	
	cout << "Address: ";
	cin.ignore();
	getline(cin, strinput);
	c.setAddress(strinput);
	
	cout << "City: ";
	cin.ignore();
	getline(cin, strinput);
	c.setCity(strinput);
	
	cout << "State: ";
	cin >> strinput;
	c.setState(strinput);
	

	cout << "\n\nSaving to Database";
	
	//Send to DB
	AddContactToDB(c);

	for (int i = 0; i < 3; i++) {
		cout << ".";
		Sleep(1000);
	}
	
	cout << "\nContact Saved!";
	Sleep(1000);

	ClearScreen();
}

//Update Contact
void UpdateContact(){
	ClearScreen();

	Contact c;
	int intinput;
	string strinput;
	int contactid;
	bool found;
	bool saved;

	UPDATE:   
	cout << "Update Contact\n---------------------\n\n";
	cout << "Enter Contact ID: ";
	cin >> intinput;

	FindContactToUpdate(intinput, found, c);

	if (found) {
		cout << "\nContact Found!\n\n";
		cout << "ID: " << c.getID() << endl;
		cout << "First Name: " << c.getFirstName() << endl;
		cout << "Last Name: " << c.getLastName() << endl;
		cout << "Email: " << c.getEmail() << endl;
		cout << "Phone: " << c.getPhone() << endl;
		cout << "Address: " << c.getAddress() << endl;
		cout << "City: " << c.getCity() << endl;
		cout << "State: " << c.getState() << endl;

		cout << "\nSelect a field to update\n-------------------------------\n";
		cout << "1 - First Name\n";
		cout << "2 - Last Name\n";
		cout << "3 - Email\n";
		cout << "4 - Phone\n";
		cout << "5 - Address\n";
		cout << "6 - City\n";
		cout << "7 - State\n";
		cin >> intinput;

		cout << "Enter the new value: ";
		cin.ignore();
		getline(cin, strinput);

		contactid = c.getID();
UpdateContactOnDB(intinput, strinput, contactid, saved);

cout << "\n\nSaving to Database";

//Send to DB
AddContactToDB(c);

for (int i = 0; i < 3; i++) {
	cout << ".";
	Sleep(1000);
}

cout << "\nContact Saved!";
Sleep(1000);

ClearScreen();
	}
	else {
	cout << "Contact ID not found...\n\n";
	cout << "Search again? Y/N: ";
	cin >> strinput;
	if (strinput == "Y" || strinput == "y") {
		ClearScreen();
		goto UPDATE;
	}
	}
}

//View Contact
void ViewContact() {
	ClearScreen();

	Contact c;
	int intinput;
	string strinput;
	int contactid;
	bool found;


VIEW:
	cout << "View Contact\n---------------------\n\n";
	cout << "Enter Contact ID: ";
	cin >> intinput;

	FindContactToUpdate(intinput, found, c);

	if (found) {
		cout << "\nContact Found!\n\n";
		cout << "ID: " << c.getID() << endl;
		cout << "First Name: " << c.getFirstName() << endl;
		cout << "Last Name: " << c.getLastName() << endl;
		cout << "Email: " << c.getEmail() << endl;
		cout << "Phone: " << c.getPhone() << endl;
		cout << "Address: " << c.getAddress() << endl;
		cout << "City: " << c.getCity() << endl;
		cout << "State: " << c.getState() << endl;

		cout << "Search again? Y/N: ";
		cin >> strinput;
		if (strinput == "Y" || strinput == "y") {
			ClearScreen();
			goto VIEW;
		}
		ClearScreen();
	}
	else {
		cout << "Contact ID not found...\n\n";
		cout << "Search again? Y/N: ";
		cin >> strinput;
		if (strinput == "Y" || strinput == "y") {
			ClearScreen();
			goto VIEW;
		}
	}
}

//Add Log
void AddLog() {
	ClearScreen();
	int intinput;
	int noteid;
	string strinput;
	string contactname;
	bool found = false;
	string note;

	LOGS:

	cout << "Log\n---------------------\n\n";
	cout << "Enter Contact ID: ";
	cin >> intinput;

	FindContact(intinput, found, contactname);
	LastNote(noteid);

	if (found) {
		cout << "\nContact: " << contactname << "\n-------------------------\n\n";

		DisplayLogs(intinput);

		cout << "Add Note? Y/N: ";
		cin >> strinput;
		cin.ignore();
		if (strinput == "Y" || strinput == "y"){
			cout << "Note: ";
			
			//cin.ignore();
			getline(cin,note);

			SaveLog(note, intinput, noteid);
			cout << "Note saved to log!";
			Sleep(2000);

			ClearScreen();
		}
		ClearScreen();
	}
	else {
		cout << "Contact ID not found...\n\n";
		cout << "Search again? Y/N: ";
		cin >> strinput;
		if (strinput == "Y" || strinput == "y") {
			ClearScreen();
			goto LOGS;
		}
	}
}

void Report() {
	ClearScreen();

	string test;

	cout << "Report of all contacts\n-------------------------\n\n";

	PrintAllContacts();


	cout << "Press ENTER to exit";
	cin.ignore();
	getchar();
	//cin >> test;

	ClearScreen();

}

void PrintToFile() {
	cout << "\n\nGenerating File";

	PrintAllContactsToFile();

	for (int i = 0; i < 3; i++) {
		cout << ".";
		Sleep(1000);
	}

	cout << "\nReport generated on file!";
	Sleep(1000);

	ClearScreen();
}

//*********************************************************************