#pragma once

#include <iostream>
#include <vector>
#include <string>

typedef int ID;
typedef float PRICE;

class Drug {
protected:
	std::string name;
	ID id;
	PRICE price;
	std::string producent;
	int waiting_time;
public:
	Drug(std::string name, ID id, PRICE price, std::string producent, int waiting_time = 0) :
		name(name), id(id), price(price), producent(producent), waiting_time(waiting_time) {};

	virtual ~Drug() {};
	virtual void printInformation() const = 0;

	void setWaitingTime(int waiting_time) {
		this->waiting_time = waiting_time;
	}
};

class DrugNonPrescription : public Drug {
	bool need_prescription = false;

public:
	DrugNonPrescription(std::string name, ID id, PRICE price, std::string producent, int waiting_time = 0) :
		Drug(name, id, price, producent, waiting_time) {};

	void printInformation() const override {
		std::cout << "This drug is called " << this->name << std::endl;
		std::cout << "Its ID is " << this->id << std::endl;
		std::cout << "It can be sold without any prescription" << std::endl;
		std::cout << "Its price equals " << this->price << std::endl;
		std::cout << "It was made by " << this->producent << std::endl;
	}
};

class DrugWithPrescription : public Drug {
	bool need_prescription = true;

public:
	DrugWithPrescription(std::string name, ID id, PRICE price, std::string producent, int waiting_time = 0) :
		Drug(name, id, price, producent, waiting_time) {};

	void printInformation() const override {
		std::cout << "This drug is called " << this->name << std::endl;
		std::cout << "Its ID is " << this->id << std::endl;
		std::cout << "It cannot be sold without any prescription" << std::endl;
		std::cout << "Its price equals " << this->price << std::endl;
		std::cout << "It was made by " << this->producent << std::endl;
	}
};
