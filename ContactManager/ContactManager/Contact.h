#pragma once
#include <string>

using namespace std;

class Contact
{
private:
	int id;
	string firstname;
	string lastname;
	string email;
	string phone;
	string address;
	string city;
	string state;

public:
	void setID(int i);
	
	void setFirstName(string f);

	void setLastName(string l);

	void setEmail(string e);
	
	void setPhone(string p);

	void setAddress(string a);

	void setCity(string c);

	void setState(string s);

	int getID();

	string getFirstName();

	string getLastName();

	string getEmail();

	string getPhone();

	string getAddress();

	string getCity();

	string getState();
};

