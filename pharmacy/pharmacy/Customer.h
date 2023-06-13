#pragma once
#include <iostream>
#include <vector>
#include <string>

typedef int ID;


class Customer {
	ID id;
	std::string name;
	int receipt = 0;
public:
	Customer(ID id, std::string name) :
		id(id), name(name) {};

	Customer() {};

	std::string getName() {
		return name;
	}
	ID getID() {
		return id;
	}

	int getReceipt() {
		return receipt;
	}

	void addToReceipt(int newItem) {
		receipt += newItem;
	}
	friend std::ostream& operator<< (std::ostream& out, const Customer& customer) {
		out << "ID: " << customer.id << " Name: " << customer.name << std::endl;
		return out;
	}
	friend std::istream& operator>> (std::istream& in, Customer& customer) {
		in >> customer.id;
		in >> customer.name;
		return in;
	}
	
};
