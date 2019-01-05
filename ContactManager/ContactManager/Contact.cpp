#include "pch.h"
#include "Contact.h"


void Contact::setID(int i) {
	id = i;
}

void Contact::setFirstName(string f) {
	firstname = f;
}

void Contact::setLastName(string l) {
	lastname = l;
}

void Contact::setEmail(string e) {
	email = e;
}

void Contact::setPhone(string p) {
	phone = p;
}

void Contact::setAddress(string a) {
	address = a;
}

void Contact::setCity(string c) {
	city = c;
}

void Contact::setState(string s) {
	state = s;
}

int Contact::getID() {
	return id;
}

string Contact::getFirstName() {
	return firstname;
}

string Contact::getLastName() {
	return lastname;
}

string Contact::getEmail() {
	return email;
}

string Contact::getPhone() {
	return phone;
}

string Contact::getAddress() {
	return address;
}

string Contact::getCity() {
	return city;
}

string Contact::getState() {
	return state;
}