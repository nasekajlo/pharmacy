#pragma once
#include <iostream>
#include <vector>
#include <string>

typedef int ID;

class Seller {
	ID id;
	std::string name;
public:
	Seller(ID id, std::string name) :
		id(id), name(name) {};

	//only << because you cannot be a seller
	friend std::ostream& operator<< (std::ostream& out, const Seller& seller);
};

std::ostream& operator<< (std::ostream& out, const Seller& seller)
{
	out << "Hi, I am a seller, my ID: " << seller.id << " and my name is " << seller.name << std::endl;
	return out;
}
